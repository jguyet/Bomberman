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
	return ;
}

std::ostream &				operator<<(std::ostream & o, UIInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

Tag							*UIInterface::getElementById(const char *id)
{
	std::ostringstream os;

	os << id;
	if (this->elements.count(os.str()) == 0)
		return NULL;
	return (this->elements[os.str()]);
}

// ###############################################################

void replaceAll(std::string& source, const std::string& from, const std::string& to)
{
    std::string newString;
    newString.reserve(source.length());  // avoids a few memory allocations

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while(std::string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr(lastPos);

    source.swap(newString);
}

void						UIInterface::initialize( std::string const &ui_file )
{
	//TODO build elements
	this->ui_file = "themes/" + ui_file;
	file_get_contents(this->content, this->ui_file.c_str());
	replaceAll(this->content, "\n", "");
	replaceAll(this->content, "\t", "");
	build_lexer();
	build_parser(this->content);
}

int							UIInterface::scoop_enter(std::string const & value)
{
	std::string line = split(value, '>').at(0);
	std::string tag_line;
	std::string tag_name = "unknow";
	std::string content;
	int offset = 1;

	try {
		if (line.size() <= 3 || line[0] == '/' || line[1] == '/') {
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
			if (value.find(endtag) == std::string::npos)
				throw std::exception();
			content = value.substr(tag_line.size() + 2);
			content = content.substr(0, content.find(endtag));
			offset = (tag_line.size() + 1) + content.size() + endtag.size();
		}
		if (tag_line.size() == tag_name.size())
			tag_line = "";
		else
			tag_line = tag_line.substr(tag_name.size() + 1);
		content = trim(content);
		if (this->lexer_tag.count(tag_name) == 1) {//add new Element
			(*this.*this->lexer_tag[tag_name])(tag_name, tag_line, content);
		}
	} catch (std::exception e) {
		std::cerr << this->ui_file << " error syntax on tag <" << tag_name << ">" << std::endl;
		offset = line.size();
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
	std::cout << "-> " << tag_name << "|" << tag_params << "|" << trimcontent << std::endl;
	trimcontent = content.substr(1, content.size() - 2);
	parameters = split(trimcontent, ',');
	for (int i = 0; i < parameters.size(); i++) {
		std::vector<std::string> param_split = split(parameters.at(i), ':');

		if (param_split.size() != 2)
			continue;
		std::string key = trim(param_split.at(0));
		std::string value = trim(param_split.at(1));

		if (value.size() > 2 && value.find("\"") != std::string::npos) {
			value = value.substr(1, value.size() - 2);
		}
		parameters_map[key] = value;

		std::cout << key << ":" << value << std::endl;
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
				width = BombermanClient::instance->screen->width * width / 100;
			}
			if (parameters_map["height"].find("%") != std::string::npos) {
				height = BombermanClient::instance->screen->height * height / 100;
			}

			tag = new Image(parameters_map["src"].c_str(), w, h, width, height);
		} else {
			tag = new Image(parameters_map["src"].c_str());
		}
	} else if (tag_name == "text") {
		std::string text = parameters_map.count("value") ? parameters_map["value"] : "";
		tag = new Text(text, "");
	}

	if (tag != NULL) {
		this->elements[parameters_map["id"]] = tag;
	}
}

void						UIInterface::addStyle(std::string const &tag_name, std::string const &tag_params, std::string const &content)
{
	// std::string trimcontent;
	// std::vector<std::string> parameters;
	// std::map<std::string, std::string> parameters_map;
    //
	// if (content.size() == 0 || content[0] != '{' || content[content.size() - 1] != '}') {
	// 	return ;
	// }
	std::cout << "-> " << tag_name << "|" << tag_params << "|" << content << std::endl;
}

void						UIInterface::build_lexer( void )
{
	this->lexer["<"] = &UIInterface::scoop_enter;

	this->lexer_tag["style"] = &UIInterface::addStyle;
	this->lexer_tag["img"] = &UIInterface::addElement;
	this->lexer_tag["button"] = &UIInterface::addElement;
	this->lexer_tag["input"] = &UIInterface::addElement;
	this->lexer_tag["text"] = &UIInterface::addElement;
	this->lexer_tag["div"] = &UIInterface::addElement;
}

void						UIInterface::build_parser( std::string const & content )
{
	for (int i = 0; i < content.size(); i++) {
		std::ostringstream os;
		os << content[i];
		if (this->lexer.count(os.str()) == 0)
			continue ;

		int offset = (*this.*this->lexer[os.str()])(content.substr(i));

		i += offset - 1;
	}
}
