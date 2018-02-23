#include "Bomberman.hpp"
#include "Packet.hpp"
#include "messages/ActionMessage.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

CharacterControllerScript::CharacterControllerScript ( int playerId )
{
	this->playerId = playerId;
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

	ActionType type = ActionType::TYPE_BOMB;
	ActionObject object(type, fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), c->position.y, fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));

	Packet packet(new ActionMessage(object, this->getPlayerId()));
	packet.sendPacket(BombermanClient::instance->sock->getSocket());

	// GameObject *bomb = Factory::newBomb(this);
	// bomb->transform.position = glm::vec3(c->position.x,0,c->position.z);
	// bomb->transform.scale = glm::vec3(1.5f,1.5f,1.5f);
	// bomb->transform.rotation = glm::vec3(0,0,0);
	// BombermanClient::instance->current_scene->add(bomb);
	// c->obstacle = bomb;
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
	static AI robot = AI(this->gameObject);
	int currentPlayerId = -1;
	GameScene* scene = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene);

	if (scene->current_player != NULL)
	{
		CharacterControllerScript *controllerScript = ((CharacterControllerScript*)scene->current_player->GetComponent<Script>());
		if (controllerScript) {
			currentPlayerId = controllerScript->getPlayerId();
		}
	}

	if (this->playerId == currentPlayerId) {
		if (KeyBoard::instance->getKey(SDL_SCANCODE_Q))//Q
			this->Attack();
		//if (KeyBoard::instance->getKey(SDL_SCANCODE_P))
			//BombermanClient::instance->current_scene->add(Factory::newPowerUp(fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0)));

		this->has_moved = false;
		if (KeyBoard::instance->getKey(SDL_SCANCODE_RIGHT)) //RIGHT
			this->MRight();
		else if (KeyBoard::instance->getKey(SDL_SCANCODE_LEFT))//LEFT
			this->MLeft();
		else if (KeyBoard::instance->getKey(SDL_SCANCODE_UP))//UP
			this->MUp();
		else if (KeyBoard::instance->getKey(SDL_SCANCODE_DOWN))//DOWN
			this->MDown();
		else if (KeyBoard::instance->getKey(SDL_SCANCODE_E))
			std::cout << "X:" << this->gameObject->transform.position.x << "Z:" << this->gameObject->transform.position.z << " " << std::endl;

		if (this->has_moved && this->lastNetwork < (TimeUtils::getCurrentSystemMillis() - 50L)) {
			BombermanClient::instance->sock->updateMovement(this);
			this->lastNetwork = TimeUtils::getCurrentSystemMillis();
			this->gameObject->GetComponent<Animator>()->handleAnimation("walk");
		} else {
			this->gameObject->GetComponent<Animator>()->handleAnimation("idle");
		}
	}
	else if (this->playerId == 100)
	{
		int i = 0;
		// this->gameObject->transform.position.x, this->gameObject->transform.position.z
		i = robot.brain();
		this->has_moved = false;
		if (i != 0)
			(this->*cmd[i])();


		if (this->has_moved) {
			this->gameObject->GetComponent<Animator>()->handleAnimation("walk");
			BombermanClient::instance->sock->updateMovement(this);
		} else {
			this->gameObject->GetComponent<Animator>()->handleAnimation("idle");
		}
		// RIGHT KeyBoard::instance->getKey(SDL_SCANCODE_KP_6)
		// LEFT KeyBoard::instance->getKey(SDL_SCANCODE_KP_4s)
		// UP KeyBoard::instance->getKey(SDL_SCANCODE_KP_8)
		// DOWN KeyBoard::instance->getKey(SDL_SCANCODE_KP_2)
	}
}

void								CharacterControllerScript::OnPreRender(void)
{

}

void								CharacterControllerScript::OnEndRender(void)
{

}

void						CharacterControllerScript::OnCollisionEnter(GameObject *collider)
{

	if (dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->current_player == NULL)
		return ;
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
		if (this->gameObject == dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->current_player) {
			// BombermanClient::instance->current_scene = new MainMenuScene();
			// dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->current_player = NULL;
			// Something bad happens when we delete the current player, so why we need to delete?
			exit(-1);
		} else {
			printf("Player id %d is dead !\n", this->getPlayerId());
			dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->removePlayer(this->gameObject);
			this->gameObject->toDelete = true;
		}
	}
	else if (collider->tag == "bonus-bomb-up")
	{
		//std::cout << " bomb-up  " << this->gameObject->tag << " New Bomb add " << std::endl;
		this->bomb++;
		collider->toDelete = true;
	}
	else if (collider->tag == "bonus-power-up")
	{
		//std::cout << " power-up  " << this->gameObject->tag << " New power add " << std::endl;
		this->power++;
		collider->toDelete = true;
	}
	else if (collider->tag == "bonus-speed-up")
	{
		//std::cout << " speed-up  " << this->gameObject->tag << " New speed add " << std::endl;
		this->speed+= 0.003;
		collider->toDelete = true;
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

int 										CharacterControllerScript::getPlayerId()
{
	return this->playerId;
}

int 										CharacterControllerScript::getPower()
{
	return this->power;
}
// ###############################################################
