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
	this->content.clear();
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

Case						*Map::getCase(int x, int z)
{
	return &this->content[std::make_pair(x, z)];
}

// ###############################################################
