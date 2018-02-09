#include "Bomberman.hpp"

// STATIC ########################################################

GameObject							*Factory::newBlock(std::string model)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Block";
	obj->AddComponent<Model>(Model::model[model]);
	return (obj);
}

GameObject							*Factory::newPlayer(void)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Player";
	obj->AddComponent<Model>(Model::model["bomberman"]);
	return (obj);
}

// ###############################################################

// CANONICAL #####################################################

Factory::Factory ( void )
{
	return ;
}

Factory::Factory ( Factory const & src )
{
	*this = src;
	return ;
}

Factory &				Factory::operator=( Factory const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Factory::~Factory ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Factory const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
