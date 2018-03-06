#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

UIInterface::UIInterface ( std::string const &ui_file )
{
	this->initialize(ui_file);
	return ;
}

UIInterface::UIInterface ( UIInterface const & src )
{
	*this = src;
	return ;
}

UIInterface &				UIInterface::operator=( UIInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

UIInterface::~UIInterface ( void )
{
	this->clearElements();
	this->elements_params.clear();
	this->styles.clear();
	this->conditions.clear();
	return ;
}

std::ostream &				operator<<(std::ostream & o, UIInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						UIInterface::clearElements(void)
{
	for (std::map<std::string, Tag*>::iterator it = this->elements.begin(); it != this->elements.end(); it++)
	{
		Tag *tmp = it->second;

		delete tmp;
	}
	this->elements.clear();
}

Tag							*UIInterface::getElementById(const char *id)
{
	std::ostringstream os;

	os << id;
	if (this->elements.count(os.str()) == 0)
		return NULL;
	return (this->elements[os.str()]);
}

// ###############################################################

bool					UIInterface::initialize( std::string const &ui_file )
{
	//TODO build elements
	this->ui_file = ui_file;
	std::ifstream ifs(this->ui_file.c_str());

	if (!ifs)
		return false;
	int date = 0;
	struct stat result;
	if(stat(this->ui_file.c_str(), &result)!=0)
		return false;
	date = result.st_mtime;
	if (this->last_modified_date == date)
		return false;
	if (this->last_modified_date != 0) {
		this->clearElements();
		this->elements_params.clear();
		this->styles.clear();
		this->conditions.clear();
	}
	this->last_modified_date = date;
	file_get_contents(this->content, this->ui_file.c_str());
	replaceAll(this->content, "\n", "");
	replaceAll(this->content, "\t", "");
	build_lexer();
	build_parser(this->content);
	return true;
}

void						UIInterface::build(void)
{
	this->modified = false;
	if (this->initialize(this->ui_file)) {
		std::cout << this->ui_file << " Updated modification detected." << std::endl;
		this->modified = true;
	}

	for (int i = 0; i < this->conditions.size(); i++)
	{
		std::vector<std::string> cond_split = split(this->conditions.at(i), '\t');
		std::string tag_name = cond_split.at(0);
		std::string tag_params = cond_split.at(1);;
		std::string content = cond_split.at(2);
		this->buildCondition(tag_name, tag_params, content);
	}

	for (auto &element : this->elements) {
		element.second->setParent(NULL);
		if (element.second->parent_name != "" && this->elements.count(element.second->parent_name) == 1) {
			element.second->setParent(this->elements[element.second->parent_name]);
		}
	}
}

int							UIInterface::scoop_enter(std::string const & value)
{
	std::string line = split_string_without(value, ">", "\"").at(0);
	std::string tag_line;
	std::string tag_name = "unknow";
	std::string content;
	int offset = 1;

	try {
		if (line.size() <= 3 || line[0] == '/' || line[1] == '/') {
			offset = line.size();
			replaceAll(line, "<", "");
			replaceAll(line, ">", "");
			replaceAll(line, "/", "");
			tag_name = line;
			throw std::exception();
		}
		if (line[line.size() - 1] == '/') {//<img />
			tag_line = line.substr(1, line.size() - 2);
			tag_name = split(tag_line, ' ').at(0);
			content = "";
			offset = line.size() + 1;
		} else {//<img></img>
			tag_line = line.substr(1);
			tag_name = split(tag_line, ' ').at(0);
			std::string endtag = "</" + tag_name + ">";
			if (value.find(endtag) == std::string::npos) {
				offset = line.size();
				throw std::exception();
			}
			content = value.substr(tag_line.size() + 2);
			content = content.substr(0, content.find(endtag));
			offset = (tag_line.size() + 1) + content.size() + endtag.size();
		}
		if (tag_line.size() == tag_name.size())
			tag_line = "";
		else
			tag_line = trim(tag_line.substr(tag_name.size() + 1));
		content = trim(content);
		if (this->lexer_tag.count(tag_name) == 1) {//add new Element
			(*this.*this->lexer_tag[tag_name])(tag_name, tag_line, content);
		}
	} catch (std::exception e) {
		std::cerr << this->ui_file << " error syntax on tag <" << tag_name << ">" << std::endl;
	}
	return offset;
}

void						UIInterface::addElement(std::string const &tag_name, std::string const &tag_params, std::string const &content)
{
	Tag *tag = NULL;
	std::string trimcontent;
	std::vector<std::string> parameters;
	std::map<std::string, std::string> parameters_map;

	if (content.size() == 0 || content[0] != '{' || content[content.size() - 1] != '}') {
		return ;
	}
	//std::cout << "-> " << tag_name << "|" << tag_params << "|" << content << std::endl;
	trimcontent = content.substr(1, content.size() - 2);
	for (std::map<std::string, std::string>::iterator it = this->variables.begin(); it != this->variables.end(); it++) {
		if (trimcontent.find(it->first) != std::string::npos) {
			replaceAll(trimcontent, it->first, it->second);
		}
	}
	parameters = split(trimcontent, ',');
	for (int i = 0; i < parameters.size(); i++) {
		std::vector<std::string> param_split = split(parameters.at(i), ':');

		if (param_split.size() < 2)
			continue;
		std::string key = trim(param_split.at(0));
		std::string value = trim(param_split.at(1));

		for (int v = 2; v < param_split.size(); v++) {
			value += ":" + param_split.at(v);
		}

		if (value.size() > 2 && value.find("\"") != std::string::npos) {
			value = value.substr(1, value.size() - 2);
		}
		parameters_map[key] = value;
		//std::cout << key << ":" << value << std::endl;
	}
	if (parameters_map.count("id") == 0) {
		std::cerr << "Error tag <" << tag_name << "> dont have id." << std::endl;
		return ;
	}
	if (tag_name == "img" && parameters_map.count("src") == 1) {
		if (parameters_map.count("width") && parameters_map.count("height") && parameters_map.count("w") && parameters_map.count("h")) {
			int w = atoi(parameters_map["w"].c_str());
			int h = atoi(parameters_map["h"].c_str());
			int width = atoi(parameters_map["width"].c_str());
			int height = atoi(parameters_map["height"].c_str());

			if (parameters_map["width"].find("%") != std::string::npos) {
				width = width % 101;
				width = BombermanClient::getInstance()->screen->canvas_width * width / 100;
			}
			if (parameters_map["height"].find("%") != std::string::npos) {
				height = height % 101;
				height = BombermanClient::getInstance()->screen->canvas_height * height / 100;
			}

			tag = new Image(parameters_map["src"], w, h, width, height);
		} else {
			std::cerr << "Error tag <img> dont have width,height,w,h." << std::endl;
		}
	} else if (tag_name == "text") {
		std::string text = parameters_map.count("value") ? parameters_map["value"] : "";
		tag = new Text(text, "");
	} else if (tag_name == "square") {
		int x = 0;
		int y = 0;
		if (parameters_map.count("width") && parameters_map.count("height")) {
			int width = atoi(parameters_map["width"].c_str());
			int height = atoi(parameters_map["height"].c_str());

			tag = new Square(x, y, width, height);
		}
	}

	if (tag != NULL) {
		if (parameters_map.count("x") == 1) {
			tag->transform.position.x = atoi(parameters_map["x"].c_str());

			if (parameters_map["x"].find("%") != std::string::npos) {
				tag->transform.position.x = (int)tag->transform.position.x % 101;
				tag->transform.position.x = (BombermanClient::getInstance()->screen->width / 100) * tag->transform.position.x;
			}
		}
		if (parameters_map.count("y") == 1) {
			tag->transform.position.y = atoi(parameters_map["y"].c_str());

			if (parameters_map["y"].find("%") != std::string::npos) {
				tag->transform.position.y = (int)tag->transform.position.y % 101;
				tag->transform.position.y = (BombermanClient::getInstance()->screen->height / 100) * tag->transform.position.y;
			}
		}
		if (parameters_map.count("z-index") == 1) {
			tag->transform.position.z = atoi(parameters_map["z-index"].c_str());
		}
		if (parameters_map.count("parent") == 1) {
			tag->setParent_name(parameters_map["parent"]);
		}
		if (parameters_map.count("class") == 1) {
			for (std::map<std::string, std::string>::iterator it = this->styles.begin(); it != this->styles.end(); it++) {
				if (parameters_map["class"].find(it->first) != std::string::npos) {
					tag->setStyle(it->second.c_str());
				}
			}
		}

		if (parameters_map.count("style") == 1) {
			tag->setStyle(parameters_map["style"].c_str());
		}
		if (this->elements.count(parameters_map["id"]) != 0) {
			Tag *tmp = this->elements[parameters_map["id"]];

			if (tmp->equals(tag) == true) {
				delete tag;
				return ;
			}
			delete tmp;
			this->elements.erase(parameters_map["id"]);
		}
		this->elements_params[parameters_map["id"]] = parameters_map;
		this->elements[parameters_map["id"]] = tag;
		this->modified = true;
	}
}

void						UIInterface::addStyle(std::string const &tag_name, std::string const &tag_params, std::string const &content)
{
	std::string trimcontent;
	std::vector<std::string> string_split;
	std::map<std::string, std::string> style_map;

	if (content.size() == 0 || content.find("{") == std::string::npos || content.find("}") == std::string::npos) {
	 	return ;
	}
	string_split = split(content, '}');
	for (int i = 0; i < string_split.size(); i++) {
		std::vector<std::string> style_split = split(string_split.at(i), '{');

		if (style_split.size() != 2)
		 continue ;
		std::string id = style_split.at(0);
		std::string style = style_split.at(1);

		if (id[0] == '.')
			id = id.substr(1);

		this->styles[id] = style;
	}
}

void						UIInterface::buildCondition(std::string const &tag_name, std::string const &tag_params, std::string const &content)
{
	std::string params = std::string(tag_params);
	if (params.find("condition=") == std::string::npos)
		return ;
	replaceAll(params, "condition=", "");
	replaceAll(params, "\"", "");
	for (std::map<std::string, LexerConditionMethods>::iterator it = this->lexer_condition.begin(); it != this->lexer_condition.end(); it++) {
		if (params.find(it->first) != std::string::npos)
		{
			std::vector<std::string> condition_split = split_string_without(params, it->first, "\"");

			if (condition_split.size() != 2)
				return ;
			std::string var1 = trim(condition_split.at(0));
			std::string var2 = trim(condition_split.at(1));
			if (this->variables.count(var1)) {
				var1 = this->variables[var1];
			}
			if (this->variables.count(var2)) {
				var2 = this->variables[var2];
			}
			bool result = (*this.*it->second)(var1, var2);

			if (result) {
				this->build_parser(content);
			}
		}
	}
}

void						UIInterface::addCondition(std::string const &tag_name, std::string const &tag_params, std::string const &content)
{
	if (tag_name == "" || tag_params == "" || content == "")
		return ;
	std::ostringstream cond;
	cond << tag_name << "\t" << tag_params << "\t" << content;
	this->conditions.push_back(cond.str());
}

bool						UIInterface::equals(std::string const &first, std::string const &second)
{
	if (second == "NULL" && first.find("$") != std::string::npos)
		return true;
	if (first == second)
		return true;
	return false;
}

bool						UIInterface::notequals(std::string const &first, std::string const &second)
{
	if (second == "NULL" && first.find("$") != std::string::npos)
		return false;
	if (first != second)
		return true;
	return false;
}

bool						UIInterface::superior(std::string const &first, std::string const &second)
{
	if (atoi(first.c_str()) > atoi(second.c_str()))
		return true;
	return false;
}

bool						UIInterface::inferior(std::string const &first, std::string const &second)
{
	if (atoi(first.c_str()) < atoi(second.c_str()))
		return true;
	return false;
}

void						UIInterface::build_lexer( void )
{
	this->lexer["<"] = &UIInterface::scoop_enter;

	this->lexer_tag["style"] = &UIInterface::addStyle;
	this->lexer_tag["img"] = &UIInterface::addElement;
	this->lexer_tag["button"] = &UIInterface::addElement;
	this->lexer_tag["input"] = &UIInterface::addElement;
	this->lexer_tag["text"] = &UIInterface::addElement;
	this->lexer_tag["square"] = &UIInterface::addElement;
	this->lexer_tag["if"] = &UIInterface::addCondition;

	this->lexer_condition["=="] = &UIInterface::equals;
	this->lexer_condition[">="] = &UIInterface::superior;
	this->lexer_condition["<="] = &UIInterface::inferior;
	this->lexer_condition["!="] = &UIInterface::notequals;
}

void						UIInterface::build_parser( std::string const & content )
{
	for (int i = 0; i < content.size(); i++) {
		std::ostringstream os;
		os << content[i];
		if (this->lexer.count(os.str()) == 0)
			continue ;

		int offset = (*this.*this->lexer[os.str()])(content.substr(i));

		if (offset != 0)
			i += offset - 1;
	}
}
