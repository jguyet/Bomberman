#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

ExplosionControllerScript::ExplosionControllerScript ( void )
{
	return ;
}

ExplosionControllerScript::ExplosionControllerScript ( ExplosionControllerScript const & src )
{
	*this = src;
	return ;
}

ExplosionControllerScript &				ExplosionControllerScript::operator=( ExplosionControllerScript const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

ExplosionControllerScript::~ExplosionControllerScript ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, ExplosionControllerScript const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						ExplosionControllerScript::Start(void)
{
	this->startTime = TimeUtils::getCurrentSystemMillis();
}

void						ExplosionControllerScript::Update(void)
{
	if (TimeUtils::getCurrentSystemMillis() > (this->startTime + 500L)) {
		BombermanClient::instance->current_scene->remove(this->gameObject);
		delete this->gameObject;
		delete this;
	}
}

// ###############################################################
