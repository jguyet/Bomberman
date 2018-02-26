#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Properties::Properties ( std::string const &file_path )
{
	this->initialize(file_path);
	return ;
}

Properties::Properties ( Properties const & src )
{
	*this = src;
	return ;
}

Properties &				Properties::operator=( Properties const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Properties::~Properties ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Properties const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

std::string					Properties::get(std::string const &key)
{
	std::ostringstream os;
	std::string k;

	os << key;
	k = os.str();
	if (this->map.count(k) == 0)
		return "";
	return (this->map[k]);
}

int							Properties::getInt(std::string const &key)
{
	std::ostringstream os;
	std::string k;

	os << key;
	k = os.str();
	if (this->map.count(k) == 0)
		return 0;
	return (atoi(this->map[k].c_str()));
}

bool						Properties::getBool(std::string const &key)
{
	std::ostringstream os;
	std::string k;

	os << key;
	k = os.str();
	if (this->map.count(k) == 0)
		return false;
	if (this->map[k] == "true" || this->map[k] == "TRUE")
		return true;
	return false;
}

// ###############################################################

// PRIVATE METHOD ################################################

void						Properties::initialize(std::string const &file_path)
{
	this->file_path = file_path;
	file_get_contents(this->content, this->file_path);
	std::vector<std::string> stringsplit = split(this->content, '\n');

	for (int i = 0; i < stringsplit.size(); i++)
	{
		std::string					cmd_line = stringsplit.at(i);
		std::vector<std::string>	splited_line = split(cmd_line, '=');
		std::string					key;
		std::string					value;

		if (splited_line.size() < 2)
			continue ;

		key = trim(splited_line.at(0));
		value = trim(splited_line.at(1));
		this->map[key] = value;
	}
}

// ###############################################################
