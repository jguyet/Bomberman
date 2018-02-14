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

void						CharacterControllerScript::Start(void)
{

}

void						CharacterControllerScript::Update(void)
{
	if (KeyBoard::instance->getKey(SDL_SCANCODE_Q)) {//Q

		Case *c = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase( fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));

		if (c != NULL && c->walkable == true && c->obstacle == NULL) {
			GameObject *bomb = Factory::newBomb();
			bomb->transform.position = glm::vec3(c->position.x,0,c->position.z);
			bomb->transform.scale = glm::vec3(1.5f,1.5f,1.5f);
			bomb->transform.rotation = glm::vec3(0,0,0);
			BombermanClient::instance->current_scene->add(bomb);
			c->obstacle = bomb;
		}
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_RIGHT)) {//RIGHT
		if (this->gameObject->transform.rotation.y != 180.f) {
			this->gameObject->transform.rotation.y = 180.f;
		}
		this->gameObject->transform.position.z += 0.1f;
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_LEFT)) {//LEFT
		if (this->gameObject->transform.rotation.y != 0.f) {
			this->gameObject->transform.rotation.y = 0.f;
		}
		this->gameObject->transform.position.z -= 0.1f;
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_UP)) {//UP
		if (this->gameObject->transform.rotation.y != 270.f) {
			this->gameObject->transform.rotation.y = 270.f;
		}
		this->gameObject->transform.position.x += 0.1f;
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_DOWN)) {//DOWN
		if (this->gameObject->transform.rotation.y != 90.f) {
			this->gameObject->transform.rotation.y = 90.f;
		}
		this->gameObject->transform.position.x -= 0.1f;
	}
}

void						CharacterControllerScript::OnCollisionEnter(GameObject *collider)
{
	if (collider->tag == "Bomb") {
		Case *c = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase( fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));
		if ((c != NULL && c->obstacle == NULL) || (c != NULL && c->obstacle != NULL && c->obstacle->id != collider->id)) {
			BoxCollider *b = this->gameObject->GetComponent<BoxCollider>();
			//get contact point
			glm::vec3 contact_point = glm::vec3(0,0,0);
			contact_point.x = fmax(abs(this->gameObject->transform.position.x - collider->transform.position.x) - ((2.f + b->size.x)/2.f), 0);
			contact_point.y = fmax(abs(this->gameObject->transform.position.y - collider->transform.position.y) - ((2.f + b->size.y)/2.f), 0);
			contact_point.z = fmax(abs(this->gameObject->transform.position.z - collider->transform.position.z) - ((2.f + b->size.z)/2.f), 0);
			if (this->gameObject->transform.position.x <= collider->transform.position.x)
				contact_point.x = -contact_point.x;
			if (this->gameObject->transform.position.y <= collider->transform.position.y)
				contact_point.y = -contact_point.y;
			if (this->gameObject->transform.position.z <= collider->transform.position.z)
				contact_point.z = -contact_point.z;

			this->gameObject->transform.position.x += contact_point.x;
			this->gameObject->transform.position.y += contact_point.y;
			this->gameObject->transform.position.z += contact_point.z;
		}
	}
	if (collider->tag == "brick") {
		BoxCollider *b = this->gameObject->GetComponent<BoxCollider>();
		//get contact point
		glm::vec3 contact_point = glm::vec3(0,0,0);
		contact_point.x = fmax(abs(this->gameObject->transform.position.x - collider->transform.position.x) - ((2.f + b->size.x)/2.f), 0);
		contact_point.y = fmax(abs(this->gameObject->transform.position.y - collider->transform.position.y) - ((2.f + b->size.y)/2.f), 0);
		contact_point.z = fmax(abs(this->gameObject->transform.position.z - collider->transform.position.z) - ((2.f + b->size.z)/2.f), 0);
		if (this->gameObject->transform.position.x <= collider->transform.position.x)
			contact_point.x = -contact_point.x;
		if (this->gameObject->transform.position.y <= collider->transform.position.y)
			contact_point.y = -contact_point.y;
		if (this->gameObject->transform.position.z <= collider->transform.position.z)
			contact_point.z = -contact_point.z;

		this->gameObject->transform.position.x += contact_point.x;
		this->gameObject->transform.position.y += contact_point.y;
		this->gameObject->transform.position.z += contact_point.z;
	}
}

// ###############################################################
