#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

ExplosionControllerScript::ExplosionControllerScript ( long timer )
{
	this->timer = timer;
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
	this->gameObject->transform.scale = glm::vec3(0.f, 0.f, 0.f);
	this->startTime = TimeUtils::getCurrentSystemMillis();
	this->timerExplode = this->startTime;
}

void						ExplosionControllerScript::Update(void)
{

	if (TimeUtils::getCurrentSystemMillis() > (this->startTime + (this->timer * 100L))) {

	//	std::cout << "Time to explode " << std::endl;
		if (this->timerExplode < TimeUtils::getCurrentSystemMillis()) {
			std::cout << "Bigger explosion" << std::endl;
			this->gameObject->transform.scale+=0.1f;
			this->timerExplode = TimeUtils::getCurrentSystemMillis() + 1L;
		}

	}
	if (TimeUtils::getCurrentSystemMillis() > (this->startTime + (this->timer * 100L) + 500L)) {
		std::cout << "Delete" << std::endl;
		BombermanClient::instance->current_scene->remove(this->gameObject);
		delete this->gameObject;
		delete this;
	}
}

// ###############################################################
