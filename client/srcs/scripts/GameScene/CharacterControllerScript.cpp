#include "Bomberman.hpp"

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
	Case *c = dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->map->getCase( fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));
	if (c->obstacle != NULL)
		return ;
	c->walkable = false;
	this->bomb--;


	if (BombermanClient::getInstance()->sock->state) {
		ActionType type = ActionType::TYPE_BOMB;
		ActionObject object(type, fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), c->position.y, fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));
		Packet packet(new ActionMessage(object, this->getPlayerId()));
		packet.sendPacket(BombermanClient::getInstance()->sock->getSocket());
	}
	GameObject *bomb = Factory::newBomb(this);

	bomb->transform.position = glm::vec3(c->position.x,0,c->position.z);
	bomb->transform.scale = glm::vec3(1.5f,1.5f,1.5f);
	bomb->transform.rotation = glm::vec3(0,0,0);
	BombermanClient::getInstance()->current_scene->add(bomb);
	c->obstacle = bomb;
	this->in_mi_bomb = true;
	this->last_bomb_2 = this->last_bomb_1;
	this->last_bomb_1 = bomb->id;
}

void 								CharacterControllerScript::BombExplode()
{
	this->bomb++;
}

void								CharacterControllerScript::MUp(void)
{
	if (this->locked)
		return ;
	if (this->gameObject->transform.rotation.y != 270.f) {
		this->gameObject->transform.rotation.y = 270.f;
	}
	this->gameObject->transform.position.x += this->speed;
	this->has_moved = true;
}

void								CharacterControllerScript::MDown(void)
{
	if (this->locked)
		return ;
	if (this->gameObject->transform.rotation.y != 90.f) {
		this->gameObject->transform.rotation.y = 90.f;
	}
	this->gameObject->transform.position.x -= this->speed;
	this->has_moved = true;
}

void								CharacterControllerScript::MLeft(void)
{
	if (this->locked)
		return ;
	if (this->gameObject->transform.rotation.y != 0.f) {
		this->gameObject->transform.rotation.y = 0.f;
	}
	this->gameObject->transform.position.z -= this->speed;
	this->has_moved = true;
}

void								CharacterControllerScript::MRight(void)
{
	if (this->locked)
		return ;
	if (this->gameObject->transform.rotation.y != 180.f) {
		this->gameObject->transform.rotation.y = 180.f;
	}
	this->gameObject->transform.position.z += this->speed;
	this->has_moved = true;
}

void						CharacterControllerScript::Update(void)
{
	if (this->collide_with_mi_bomb == false)
		this->in_mi_bomb = false;
	this->lastPosition = glm::vec3(this->gameObject->transform.position.x, this->gameObject->transform.position.y, this->gameObject->transform.position.z);
	static std::map<int, P> cmd = {
		std::make_pair(SDL_SCANCODE_Q, &CharacterControllerScript::Attack), std::make_pair(SDL_SCANCODE_UP, &CharacterControllerScript::MUp),
		std::make_pair(SDL_SCANCODE_DOWN, &CharacterControllerScript::MDown), std::make_pair(SDL_SCANCODE_LEFT, &CharacterControllerScript::MLeft),
		std::make_pair(SDL_SCANCODE_RIGHT, &CharacterControllerScript::MRight)
	};


	int currentPlayerId = -1;
	GameScene* scene = dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene);


	if (scene->current_player != NULL)
	{
		CharacterControllerScript *controllerScript = ((CharacterControllerScript*)scene->current_player->GetComponent<Script>());
		if (controllerScript) {
			currentPlayerId = controllerScript->getPlayerId();
		}
	}

	this->has_moved = false;

	if (this->playerId == currentPlayerId) {
		if (KeyBoard::instance->getKey(SDL_SCANCODE_Q))//Q
		{
			this->Attack();
			// std::cout << std::endl;
		}
		//if (KeyBoard::instance->getKey(SDL_SCANCODE_P))
			//BombermanClient::getInstance()->current_scene->add(Factory::newPowerUp(fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0)));
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

		if (this->lastNetwork < TimeUtils::getCurrentSystemMillis() - 100L )
		{
			BombermanClient::getInstance()->sock->updateMovement(this);
			this->lastNetwork = TimeUtils::getCurrentSystemMillis();
		}

		if (this->has_moved) {
			if (this->lastNetwork < (TimeUtils::getCurrentSystemMillis() - 50L)) {
				BombermanClient::getInstance()->sock->updateMovement(this);
				this->lastNetwork = TimeUtils::getCurrentSystemMillis();
			}
			this->gameObject->GetComponent<Animator>()->handleAnimation("walk");
		} else {
			this->gameObject->GetComponent<Animator>()->handleAnimation("idle");
		}
	}
	else if (this->playerId == 100)
	{
		static AI robot = AI(this->gameObject);
		int i = 0;
		i = robot.brain();

		this->has_moved = false;
		if (i != 0)
			(this->*cmd[i])();

		if (this->has_moved) {
			this->gameObject->GetComponent<Animator>()->handleAnimation("walk");
			BombermanClient::getInstance()->sock->updateMovement(this);
		} else {
			this->gameObject->GetComponent<Animator>()->handleAnimation("idle");
		}
		// RIGHT KeyBoard::instance->getKey(SDL_SCANCODE_KP_6)
		// LEFT KeyBoard::instance->getKey(SDL_SCANCODE_KP_4s)
		// UP KeyBoard::instance->getKey(SDL_SCANCODE_KP_8)
		// DOWN KeyBoard::instance->getKey(SDL_SCANCODE_KP_2)
	} else { //other players
		if (this->lastNetwork < (TimeUtils::getCurrentSystemMillis() - 100L)) {
			if (this->gameObject->transform.position != this->lastPosition_direction)
				this->has_moved = true;
			if (this->has_moved) {
				if ((this->gameObject->transform.position.z - this->lastPosition_direction.z) > 0) {
					this->gameObject->transform.rotation.y = 180.f;
				}
				if ((this->gameObject->transform.position.z - this->lastPosition_direction.z) < 0) {
					this->gameObject->transform.rotation.y = 0.f;
				}
				if ((this->gameObject->transform.position.x - this->lastPosition_direction.x) > 0) {
					this->gameObject->transform.rotation.y = 270.f;
				}
				if ((this->gameObject->transform.position.x - this->lastPosition_direction.x) < 0) {
					this->gameObject->transform.rotation.y = 90.f;
				}
				this->gameObject->GetComponent<Animator>()->handleAnimation("walk");
			} else {
				this->gameObject->GetComponent<Animator>()->handleAnimation("idle");
			}
			this->lastPosition_direction = glm::vec3(this->gameObject->transform.position.x, this->gameObject->transform.position.y, this->gameObject->transform.position.z);
			this->lastNetwork = TimeUtils::getCurrentSystemMillis();
		}
	}
	this->collide_with_mi_bomb = false;
}

void								CharacterControllerScript::OnPreRender(void)
{
	//bind shader
	Model *playerObjectModel = this->gameObject->GetComponent<Model>();
	glUseProgram(playerObjectModel->shader);
	playerObjectModel->shaderBind = true;

	glm::vec3 colors = glm::vec3(0.8f,0.1f,0.0f);
	if (this->gameObject == dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->current_player)
		colors = glm::vec3(0.0f,0.1f,0.8f);
	glUniform3fv(playerObjectModel->color,1 , &colors[0]);
}

void								CharacterControllerScript::OnEndRender(void)
{
	//unbind shader

}

void						CharacterControllerScript::OnCollisionEnter(GameObject *collider)
{
	if (dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->current_player == NULL)
		return ;
	Case *c = dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->map->getCase( fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));

	if (c == NULL)
		return ;

	if (collider->tag == "Bomb") {
		BombControllerScript *script = dynamic_cast<BombControllerScript*>(collider->GetComponent<Script>());
		if (script->playerController->gameObject->id == this->gameObject->id) {
			this->collide_with_mi_bomb = true;
		}
		if (collider->id == this->last_bomb_1 || collider->id == this->last_bomb_2) {
		} else {
			this->in_mi_bomb = false;
		}
		if (this->in_mi_bomb == false) {//si c'est pas ma derniere bomb je suis bloquer
			this->gameObject->transform.position.x = this->lastPosition.x;
			this->gameObject->transform.position.z = this->lastPosition.z;
		}
		//}
	}
	else if (collider->tag == "Explosion") {
		if (this->gameObject == dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->current_player) {
			BombermanClient::getInstance()->sock->playerDead(this->getPlayerId());
			GameObject *gameObject = dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->current_player;
			dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->current_player = NULL;
			gameObject->toDelete = true;
		} else {
			printf("Player id %d is dead !\n", this->getPlayerId());
			dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->removePlayer(this->gameObject);
			this->gameObject->toDelete = true;
		}
	}
	else if (collider->tag == "bonus-bomb-up") {
		this->bomb++;
		collider->toDelete = true;
	}
	else if (collider->tag == "bonus-power-up") {
		this->power++;
		collider->toDelete = true;
	}
	else if (collider->tag == "bonus-speed-up") {
		this->speed+= 0.003;
		collider->toDelete = true;
		this->speed_count++;
	}
	else if (collider->tag == "Player") {

	}
	else {
		this->gameObject->transform.position.x = this->lastPosition.x;
		this->gameObject->transform.position.z = this->lastPosition.z;
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
