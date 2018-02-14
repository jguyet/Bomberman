#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

CharacterControllerScript::CharacterControllerScript ( void )
{
	return ;
}

CharacterControllerScript::CharacterControllerScript ( CharacterControllerScript const & src )
{
	*this = src;
	return ;
}

CharacterControllerScript &				CharacterControllerScript::operator=( CharacterControllerScript const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

CharacterControllerScript::~CharacterControllerScript ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, CharacterControllerScript const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						CharacterControllerScript::Update(void)
{
	if (this->collide) {
		for (int i = 0; i < this->colliders.size(); i++) {

			//std::cout << "COLLIDE WITH " << this->colliders.at(i)->tag << " (" << abs(this->gameObject->transform.position.x - this->colliders.at(i)->transform.position.x) << "," << abs(this->gameObject->transform.position.z - this->colliders.at(i)->transform.position.z) << ")" << std::endl;
			if (this->colliders.at(i)->tag != "grass") {
				//this->gameObject->transform.position.x -= (2+0.25f) - (this->gameObject->transform.position.x - this->colliders.at(i)->transform.position.x);
				//this->gameObject->transform.position.z -= (2+0.25f) - (this->gameObject->transform.position.z - this->colliders.at(i)->transform.position.z);
			}
		}
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_RIGHT)) {//RIGHT
		if (this->gameObject->transform.rotation.y != 180.f) {
			this->gameObject->transform.rotation.y = 180.f;
		}
		this->gameObject->transform.position.z += 0.1f;
	}
	else if (KeyBoard::instance->getKey(SDL_SCANCODE_LEFT)) {//LEFT
		if (this->gameObject->transform.rotation.y != 0.f) {
			this->gameObject->transform.rotation.y = 0.f;
		}
		this->gameObject->transform.position.z -= 0.1f;
	}
	else if (KeyBoard::instance->getKey(SDL_SCANCODE_UP)) {//UP
		if (this->gameObject->transform.rotation.y != 270.f) {
			this->gameObject->transform.rotation.y = 270.f;
		}
		this->gameObject->transform.position.x += 0.1f;
	}
	else if (KeyBoard::instance->getKey(SDL_SCANCODE_DOWN)) {//DOWN
		if (this->gameObject->transform.rotation.y != 90.f) {
			this->gameObject->transform.rotation.y = 90.f;
		}
		this->gameObject->transform.position.x -= 0.1f;
	}
}

// ###############################################################
