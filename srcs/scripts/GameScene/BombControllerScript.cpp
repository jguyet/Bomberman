#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

BombControllerScript::BombControllerScript ( void )
{
	this->startTime = TimeUtils::getCurrentSystemMillis();
	return ;
}

BombControllerScript::BombControllerScript ( BombControllerScript const & src )
{
	*this = src;
	return ;
}

BombControllerScript &				BombControllerScript::operator=( BombControllerScript const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

BombControllerScript::~BombControllerScript ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, BombControllerScript const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void								BombControllerScript::Update(void)
{
	if (TimeUtils::getCurrentSystemMillis() > this->startTime + 5000L) {
		this->explode();
	}
}

void								BombControllerScript::explode(void)
{
	BombermanClient::instance->current_scene->remove(this->gameObject);
	delete this->gameObject;
	delete this;
}

// ###############################################################
