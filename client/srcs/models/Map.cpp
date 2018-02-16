#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Map::Map(std::string name)
{
	this->name = name;
}

Map::Map ( Map const & src )
{
	*this = src;
	return ;
}

Map &				Map::operator=( Map const & rhs )
{
	return (*this);
}

Map::~Map ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Map const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

std::string									Map::getName()
{
	return this->name;
}

std::map<std::pair<int, int>, Case>			Map::getContent()
{
	return this->content;
}

Case						*Map::getCase(int x, int z)
{
	 return &this->content[std::make_pair(x, z)];
}

// ###############################################################
