#include "Bomberman.hpp"
#include "AI/AI.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

CharacterControllerScript::CharacterControllerScript ( int playerId )
{
	this->playerId = playerId;
	this->unlockCharacterDirections();
	Random random;

	this->color = glm::vec3(((float)random.getRandom(1,255) / 255.f), ((float)random.getRandom(1,255) / 255.f), ((float)random.getRandom(1,255) / 255.f));
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

void						CharacterControllerScript::unlockCharacterDirections(void)
{
	this->lock_direction[DIRECTION_RIGHT] = false;
	this->lock_direction[DIRECTION_LEFT] = false;
	this->lock_direction[DIRECTION_FORWARD] = false;
	this->lock_direction[DIRECTION_BACKWARD] = false;
}

void						CharacterControllerScript::Start(void)
{
	this->scene = BombermanClient::getInstance()->getCurrentScene<GameScene>();
}

void								CharacterControllerScript::Attack(void)
{
	if (this->bomb <= 0)
		return ;
	Case *c = this->scene->map->getCase( fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));
	if (c->obstacle != NULL)
		return ;
	c->walkable = false;
	this->bomb--;

	if (BombermanClient::getInstance()->sock && BombermanClient::getInstance()->sock->state) {
		ActionType type = ActionType::TYPE_BOMB;
		ActionObject object(type, fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), c->position.y, fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));
		Packet packet(new ActionMessage(object, this->getPlayerId()));
		packet.sendPacket(BombermanClient::getInstance()->sock->getSocket());
	} else {
		GameObject *bomb = Factory::newBomb(this);
		bomb->transform.position = glm::vec3(c->position.x,0,c->position.z);
		bomb->transform.scale = glm::vec3(1.5f,1.5f,1.5f);
		bomb->transform.rotation = glm::vec3(0,0,0);
		this->scene->add(bomb);
		c->obstacle = bomb;
	}
}

void 								CharacterControllerScript::BombExplode()
{
	this->bomb++;
}

void								CharacterControllerScript::MUp(void)
{
	if (this->locked || this->lock_direction[DIRECTION_FORWARD])
		return ;
	if (this->gameObject->transform.rotation.y != 270.f) {
		this->gameObject->transform.rotation.y = 270.f;
	}
	this->gameObject->transform.position.x += this->speed;
	this->has_moved = true;
}

void								CharacterControllerScript::MDown(void)
{
	if (this->locked || this->lock_direction[DIRECTION_BACKWARD])
		return ;
	if (this->gameObject->transform.rotation.y != 90.f) {
		this->gameObject->transform.rotation.y = 90.f;
	}
	this->gameObject->transform.position.x -= this->speed;
	this->has_moved = true;
}

void								CharacterControllerScript::MLeft(void)
{
	if (this->locked || this->lock_direction[DIRECTION_LEFT])
		return ;
	if (this->gameObject->transform.rotation.y != 0.f) {
		this->gameObject->transform.rotation.y = 0.f;
	}
	this->gameObject->transform.position.z -= this->speed;
	this->has_moved = true;
}

void								CharacterControllerScript::MRight(void)
{
	if (this->locked || this->lock_direction[DIRECTION_RIGHT])
		return ;
	if (this->gameObject->transform.rotation.y != 180.f) {
		this->gameObject->transform.rotation.y = 180.f;
	}
	this->gameObject->transform.position.z += this->speed;
	this->has_moved = true;
}

void 						CharacterControllerScript::checkRotation()
{
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
}

void						CharacterControllerScript::Update(void)
{
	if (this->scene->startGameInterface != NULL)
		return ;
	this->lastPosition = glm::vec3(this->gameObject->transform.position.x, this->gameObject->transform.position.y, this->gameObject->transform.position.z);
	static std::map<int, P> cmd = {
		std::make_pair(SDL_SCANCODE_Q, &CharacterControllerScript::Attack), std::make_pair(SDL_SCANCODE_UP, &CharacterControllerScript::MUp),
		std::make_pair(SDL_SCANCODE_DOWN, &CharacterControllerScript::MDown), std::make_pair(SDL_SCANCODE_LEFT, &CharacterControllerScript::MLeft),
		std::make_pair(SDL_SCANCODE_RIGHT, &CharacterControllerScript::MRight)
	};

	int currentPlayerId = -1;

	if (scene->current_player != NULL)
	{
		CharacterControllerScript *controllerScript = ((CharacterControllerScript*)this->scene->current_player->GetComponent<Script>());
		if (controllerScript) {
			currentPlayerId = controllerScript->getPlayerId();
		}
	}

	this->has_moved = false;

	if (this->lastDying != 0)
	{
		if (this->startDying == 0) {
			this->startDying = TimeUtils::getCurrentSystemMillis();
		}
		if (this->lastDying < (TimeUtils::getCurrentSystemMillis() - 20L))
		{
			this->lastDying = TimeUtils::getCurrentSystemMillis();
			this->gameObject->transform.position.y -= 1;
			this->gameObject->transform.rotation.x += 10;
			this->gameObject->transform.rotation.z += 10;
		}
		if ((TimeUtils::getCurrentSystemMillis() - this->startDying) >= 1000L) {
			if (this->playerId == currentPlayerId) { // Current player
				if (BombermanClient::getInstance()->sock == NULL || BombermanClient::getInstance()->sock->state == false)
				{
					this->scene->endGame(false);
				}
				if (BombermanClient::getInstance()->sock != NULL && BombermanClient::getInstance()->sock->state == true) {
					BombermanClient::getInstance()->sock->playerDead(this->getPlayerId());
				}
				this->scene->removePlayer(this->gameObject);
			} else { // Other players
				printf("Player id %d is dead !\n", this->getPlayerId());
				this->scene->removePlayer(this->gameObject);
				this->gameObject->toDelete = true;
			}
		}
		return;
	}

	if (this->playerId == currentPlayerId) {
		if (KeyBoard::instance->getKey(SDL_SCANCODE_Q)) {
			this->Attack();
		}
		if (KeyBoard::instance->getKey(SDL_SCANCODE_P))
		{
			BombermanClient::getInstance()->current_scene->add(Factory::newPowerUp(fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0)));
		}
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

		if (this->has_moved) {
			if (this->lastNetwork < (TimeUtils::getCurrentSystemMillis() - 50L)) {
				if (BombermanClient::getInstance()->sock != NULL && BombermanClient::getInstance()->sock->state == true)
					BombermanClient::getInstance()->sock->updateMovement(this);
				this->lastNetwork = TimeUtils::getCurrentSystemMillis();
			}
			this->gameObject->GetComponent<Animator>()->handleAnimation("walk");
		} else {
			this->gameObject->GetComponent<Animator>()->handleAnimation("idle");
		}
	}
	else { //other players
		if (this->lastNetwork < (TimeUtils::getCurrentSystemMillis() - 100L)) {
			if (this->gameObject->transform.position != this->lastPosition_direction)
				this->has_moved = true;
			if (this->has_moved) {
				this->checkRotation();
				this->gameObject->GetComponent<Animator>()->handleAnimation("walk");
			} else {
				this->gameObject->GetComponent<Animator>()->handleAnimation("idle");
			}
			this->lastPosition_direction = glm::vec3(this->gameObject->transform.position.x, this->gameObject->transform.position.y, this->gameObject->transform.position.z);
			this->lastNetwork = TimeUtils::getCurrentSystemMillis();
		}
	}
	this->unlockCharacterDirections();
}

void								CharacterControllerScript::OnPreRender(void)
{
	//bind shader
	Model *playerObjectModel = this->gameObject->GetComponent<Model>();
	glUseProgram(playerObjectModel->shader);
	playerObjectModel->shaderBind = true;

	glm::vec3 colors = glm::vec3(0.8f,0.1f,0.0f);
	if (this->gameObject == this->scene->current_player)
		colors = glm::vec3(this->color.x,this->color.y,this->color.z);
	glUniform3fv(playerObjectModel->color,1 , &colors[0]);
}

void								CharacterControllerScript::OnEndRender(void)
{
	//unbind shader

}

void						CharacterControllerScript::OnCollisionEnter(GameObject *collider)
{
	if (this->lastPosition.x == 0 && this->lastPosition.y == 0 && this->lastPosition.z == 0)
		return ;
	if (collider->tag == "Background" || collider->tag == "ground_block" || collider->tag == "env")
		return ;
	if (this->scene->current_player == NULL)
		return ;
	if (collider->tag == "door" && this->gameObject->id == this->scene->current_player->id)
	{
		if (BotControllerScript::List.size() == 0 && (BombermanClient::getInstance()->sock == NULL || BombermanClient::getInstance()->sock->state == false)) // Si tous les bots sont mort !
			this->scene->endGame(true);
		return;
	}
	else if (collider->tag == "door" && this->gameObject->id != this->scene->current_player->id)
	{
		return;
	}
	Case *c = this->scene->map->getCase( fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0), fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0));

	if (collider->tag == "Goomba" && this->gameObject->tag != "Goomba")
	{
		this->lastDying = TimeUtils::getCurrentSystemMillis();
		return;
	}
	if (c == NULL)
		return ;
	if (collider->tag == "Bomb") {

		Case *bomb_case = this->scene->map->getCase( fmax(0.5f + collider->transform.position.x / 2.f, 0), fmax(0.5f + collider->transform.position.z / 2.f, 0));

		if (c == bomb_case) {
			return ;
		}
		float x = fmax(0.5f + this->gameObject->transform.position.x / 2.f, 0);
		float z = fmax(0.5f + this->gameObject->transform.position.z / 2.f, 0);

		Case *case_left = this->scene->map->getCase(x, z - 1);
		Case *case_right = this->scene->map->getCase(x, z + 1);
		Case *case_forward = this->scene->map->getCase(x + 1, z);
		Case *case_backward = this->scene->map->getCase(x - 1, z);

		if (case_left != NULL && case_left->obstacle != NULL && case_left->obstacle->tag == "Bomb")
			this->lock_direction[DIRECTION_LEFT] = true;
		if (case_right != NULL && case_right->obstacle != NULL && case_right->obstacle->tag == "Bomb")
			this->lock_direction[DIRECTION_RIGHT] = true;
		if (case_forward != NULL && case_forward->obstacle != NULL && case_forward->obstacle->tag == "Bomb")
			this->lock_direction[DIRECTION_FORWARD] = true;
		if (case_backward != NULL && case_backward->obstacle != NULL && case_backward->obstacle->tag == "Bomb")
			this->lock_direction[DIRECTION_BACKWARD] = true;
	}
	else if (collider->tag == "Explosion") {
		this->lastDying = TimeUtils::getCurrentSystemMillis();
	}
	else if (collider->tag == "bonus-bomb-up") {
		if (this->playerId < 100)
			this->bomb++;
		collider->toDelete = true;
	}
	else if (collider->tag == "bonus-power-up") {
		if (this->playerId < 100)
			this->power++;
		collider->toDelete = true;
	} else if (collider->tag == "bonus-speed-up") {
		if (this->playerId < 100)
			this->speed+= 0.003;
		collider->toDelete = true;
		this->speed_count++;
	} else if (collider->tag == "Player") {

	} else if (collider->tag == "Goomba") {

	} else {
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
