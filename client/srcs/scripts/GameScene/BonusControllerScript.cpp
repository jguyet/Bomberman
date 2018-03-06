#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

BonusControllerScript::BonusControllerScript ( void )
{
	return ;
}

BonusControllerScript::BonusControllerScript ( BonusControllerScript const & src )
{
	*this = src;
	return ;
}

BonusControllerScript &				BonusControllerScript::operator=( BonusControllerScript const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

BonusControllerScript::~BonusControllerScript ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, BonusControllerScript const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void					BonusControllerScript::Update(void)
{
	this->gameObject->transform.rotation.y = (int)(this->gameObject->transform.rotation.y + 2) % 360;
}

// ###############################################################
