#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

CharacterControllerScript::CharacterControllerScript ( int n )
{
	this->player = n;
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

void								CharacterControllerScript::Attack(void)
{
	if (this->bomb <= 0)
		return ;
	Case *c = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase( fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));
	if (c->obstacle != NULL)
		return ;
	c->walkable = false;
	this->bomb--;
	GameObject *bomb = Factory::newBomb(this);

	bomb->transform.position = glm::vec3(c->position.x,0,c->position.z);
	bomb->transform.scale = glm::vec3(1.5f,1.5f,1.5f);
	bomb->transform.rotation = glm::vec3(0,0,0);
	BombermanClient::instance->current_scene->add(bomb);
	c->obstacle = bomb;
}

void 								CharacterControllerScript::BombExplode()
{
	this->bomb++;
}

void								CharacterControllerScript::MUp(void)
{
	if (this->gameObject->transform.rotation.y != 270.f) {
		this->gameObject->transform.rotation.y = 270.f;
	}
	this->gameObject->transform.position.x += this->speed;
	this->has_moved = true;
}

void								CharacterControllerScript::MDown(void)
{
	if (this->gameObject->transform.rotation.y != 90.f) {
		this->gameObject->transform.rotation.y = 90.f;
	}
	this->gameObject->transform.position.x -= this->speed;
	this->has_moved = true;
}

void								CharacterControllerScript::MLeft(void)
{
	if (this->gameObject->transform.rotation.y != 0.f) {
		this->gameObject->transform.rotation.y = 0.f;
	}
	this->gameObject->transform.position.z -= this->speed;
	this->has_moved = true;
}

void								CharacterControllerScript::MRight(void)
{
	if (this->gameObject->transform.rotation.y != 180.f) {
		this->gameObject->transform.rotation.y = 180.f;
	}
	this->gameObject->transform.position.z += this->speed;
	this->has_moved = true;
}

void						CharacterControllerScript::Update(void)
{
	static std::map<int, P> cmd = {
		std::make_pair(SDL_SCANCODE_Q, &CharacterControllerScript::Attack), std::make_pair(SDL_SCANCODE_UP, &CharacterControllerScript::MUp),
		std::make_pair(SDL_SCANCODE_DOWN, &CharacterControllerScript::MDown), std::make_pair(SDL_SCANCODE_LEFT, &CharacterControllerScript::MLeft),
		std::make_pair(SDL_SCANCODE_RIGHT, &CharacterControllerScript::MRight)
	};
	static AI robot;

	if (this->player == 1) {
		if (this->player == 1) {
			if (KeyBoard::instance->getKey(SDL_SCANCODE_Q))//Q
				this->Attack();
			if (KeyBoard::instance->getKey(SDL_SCANCODE_P))
				BombermanClient::instance->current_scene->add(Factory::newPowerUp(fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0)));

			this->has_moved = false;
			if (KeyBoard::instance->getKey(SDL_SCANCODE_RIGHT)) //RIGHT
				this->MRight();
			else if (KeyBoard::instance->getKey(SDL_SCANCODE_LEFT))//LEFT
				this->MLeft();
			else if (KeyBoard::instance->getKey(SDL_SCANCODE_UP))//UP
				this->MUp();
			else if (KeyBoard::instance->getKey(SDL_SCANCODE_DOWN))//DOWN
				this->MDown();

			if (this->has_moved) {
				this->walk_anim = true;
			} else {
				this->walk_anim = false;
			}
		}

		if (this->has_moved) {
			this->walk_anim = true;
		} else {
			this->walk_anim = false;
		}
	}
	else if (this->player == 2)
	{
		int i = 0;
		i = robot.brain(this->gameObject->transform.position.x, this->gameObject->transform.position.z);

		this->has_moved = false;
		if (i != 0)
			(this->*cmd[i])();

		if (this->has_moved) {
			this->walk_anim = true;
		} else {
			this->walk_anim = false;
		}
		// RIGHT KeyBoard::instance->getKey(SDL_SCANCODE_KP_6)
		// LEFT KeyBoard::instance->getKey(SDL_SCANCODE_KP_4s)
		// UP KeyBoard::instance->getKey(SDL_SCANCODE_KP_8)
		// DOWN KeyBoard::instance->getKey(SDL_SCANCODE_KP_2)
	}
}

void								CharacterControllerScript::OnPreRender(void)
{
	if (this->walk_anim && (this->walk_anim_time == 0L  || TimeUtils::getCurrentSystemMillis() > this->walk_anim_time + 100L))
	{
		if (this->walk_anim_frame >= 4)
		{
			this->walk_anim_frame = 0;
		}
		std::ostringstream s;
		s << "walk_" << this->walk_anim_frame;
		std::string str = s.str();
		this->gameObject->AddComponent<Model>(Model::model[str.c_str()]);
		this->walk_anim_frame++;
		this->walk_anim_time = TimeUtils::getCurrentSystemMillis();
	} else if (this->walk_anim == false) {
		this->gameObject->AddComponent<Model>(Model::model["bomberman"]);
	}
}

void								CharacterControllerScript::OnEndRender(void)
{

}

void						CharacterControllerScript::OnCollisionEnter(GameObject *collider)
{
	Case *c = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase( fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));

	//std::cout << "OnCollisionEnter on " << collider->tag << std::endl;

	if (c == NULL)
		return ;

	if (collider->tag == "Bomb") {
		if (c->obstacle == NULL || (c->obstacle != NULL && c->obstacle->id != collider->id)) {
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
	else if (collider->tag == "Explosion")
	{
		std::cout << " DEAD " << this->gameObject->tag << " DIE " << std::endl;
	}
	else if (collider->tag == "bonus-bomb-up")
	{
		std::cout << " bomb-up  " << this->gameObject->tag << " New Bomb add " << std::endl;
		//BombermanClient::instance->current_scene->remove(collider);
		this->bomb++;
		//delete collider;
	}
	else if (collider->tag == "bonus-power-up")
	{
		std::cout << " power-up  " << this->gameObject->tag << " New power add " << std::endl;
		//BombermanClient::instance->current_scene->remove(collider);
		this->power++;
		//delete collider;
	}
	else if (collider->tag == "bonus-speed-up")
	{
		std::cout << " speed-up  " << this->gameObject->tag << " New speed add " << std::endl;
		//BombermanClient::instance->current_scene->remove(collider);
		//this->speed+= 0.003;
		//delete collider;
	}
	else
	{
		c = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase( fmax(collider->transform.position.x / 2.f, 0), fmax(collider->transform.position.z / 2.f, 0));

		if (c == NULL || c->obstacle == NULL)
			return ;
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

int 										CharacterControllerScript::getPower()
{
	return this->power;
}
// ###############################################################
