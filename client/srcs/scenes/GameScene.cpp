#include "Bomberman.hpp"
#include "managers/MapManager.hpp"
#include "managers/SaveManager.hpp"

// CANONICAL #####################################################

GameScene::GameScene (std::string selected_map)
{
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height, 0.1f, 1000000.0f);
	this->camera->transform.position = glm::vec3(-3.4917f,36.6297f,-17.5657f);
	this->camera->transform.rotation = glm::vec3(78.0803f,269.888f,0);
	this->camera->buildFPSProjection();

	this->mapManager = new MapManager(this);

	Mix_PlayMusic(BombermanClient::getInstance()->music, 1);
	this->map = this->mapManager->getMap(selected_map);
	mapManager->buildObjects(this->map);

	this->current_player = NULL;
	this->startGameInterface = NULL;
	this->quitInterface = NULL;
	this->interface = new GameInterface(this);

	if (BombermanClient::getInstance()->sock->state == false)
	{
		this->StartSolo();
	} else {
		this->startGameInterface = new StartGameInterface();
	}

	//if grab mouse
	//SDL_ShowCursor(SDL_DISABLE);
	//SDL_SetWindowGrab(BombermanClient::getInstance()->window, SDL_TRUE);
	return ;
}

void GameScene::StartSolo(void)
{
	GameObject 				*playerObject = Factory::newPlayer(1);
	playerObject->transform.scale = glm::vec3(3,3,3);
	playerObject->transform.rotation = glm::vec3(0,0,0);
	playerObject->transform.position = glm::vec3(6.0f, 1.f, 2.0f);
	this->current_player = playerObject;
	this->players.push_back(playerObject);
	this->all_player.push_back(playerObject);
	this->add(playerObject);

	// GameObject *player = Factory::newPlayer(100);
	// this->all_player.push_back(player);
	// this->players.push_back(player);
	// player->transform.position = glm::vec3(4,1,36);
	// player->transform.scale = glm::vec3(3,3,3);
	// player->transform.rotation = glm::vec3(0,0,0);
	// this->add(player);//add on scene

	// GameObject *goomba = Factory::newGoomba();
    //
	// goomba->transform.position = glm::vec3(4,1,36);
	// goomba->transform.scale = glm::vec3(0.05f,0.05f,0.05f);
	// goomba->transform.rotation = glm::vec3(0,0,0);
	// this->add(goomba);


	GameObject *goomba1 = Factory::newGoomba();

	goomba1->transform.position = glm::vec3(10,1,25);
	goomba1->transform.scale = glm::vec3(0.05f,0.05f,0.05f);
	goomba1->transform.rotation = glm::vec3(0,0,0);
	this->add(goomba1);

/*
	GameObject *goomba2 = Factory::newGoomba();

	goomba2->transform.position = glm::vec3(15,1,30);
	goomba2->transform.scale = glm::vec3(0.05f,0.05f,0.05f);
	goomba2->transform.rotation = glm::vec3(0,0,0);
	this->add(goomba2);
*/
}

void					GameScene::removePlayer(GameObject *player)
{
	for (int i = 0; i < this->players.size(); i++)
	{
		if (this->players[i] == player) {
			this->players.erase(this->players.begin() + i);
			break;
		}
	}
}

GameObject				*GameScene::findPlayer(GameObject *player)
{
	for (int i = 0; i < this->players.size(); i++)
	{
		if (this->players[i] == player) {
			return this->players[i];
		}
	}
	return NULL;
}

GameObject				*GameScene::findPlayerById(int playerId)
{
	if (this->current_player != NULL) {
		CharacterControllerScript *script = ((CharacterControllerScript*)this->current_player->GetComponent<Script>());
		if (script != NULL && script->getPlayerId() == playerId) {
			return this->current_player;
		}
	}
	for (int i = 0; i < this->players.size(); i++)
	{
		CharacterControllerScript *script = ((CharacterControllerScript*)this->players[i]->GetComponent<Script>());
		if (script != NULL && script->getPlayerId() == playerId) {
			return this->players[i];
		}
	}
	return NULL;
}

GameScene &				GameScene::operator=( GameScene const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameScene::~GameScene ( void )
{
	BombermanClient::getInstance()->delete_socket();

	if (this->current_player != NULL) {
		this->remove(this->current_player);
		delete this->current_player;
	}
	if (this->interface != NULL) {
		delete this->interface;
	}
	if (this->startGameInterface != NULL) {
		delete this->startGameInterface;
	}
	if (this->quitInterface != NULL) {
		delete this->quitInterface;
	}
	delete this->mapManager;
}

std::ostream &				operator<<(std::ostream & o, GameScene const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

void								GameScene::closeQuitInterface(void)
{
	QuitMenuInterface *tmp = this->quitInterface;
	this->quitInterface = NULL;
	delete tmp;
	if (this->current_player == NULL)
		return ;
	CharacterControllerScript *script = ((CharacterControllerScript*)this->current_player->GetComponent<Script>());
	script->locked = false;
}

void								GameScene::calculPhisics(void)
{
	if (this->interface != NULL) {
		this->interface->addPlayers();
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_ESCAPE) && this->quitInterface == NULL) {//ESC
		this->quitInterface = new QuitMenuInterface(this);
		if (this->current_player != NULL) {
			CharacterControllerScript *script = ((CharacterControllerScript*)this->current_player->GetComponent<Script>());
			script->locked = true;
		}
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_W) && this->quitInterface == NULL) {//UP
		this->camera->move(glm::vec3(0, 0, 2));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_D) && this->quitInterface == NULL) {//RIGHT
		this->camera->move(glm::vec3(2, 0, 0));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_A) && this->quitInterface == NULL) {//LEFT
		this->camera->move(glm::vec3(-2, 0, 0));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_S) && this->quitInterface == NULL) {//DOWN
		this->camera->move(glm::vec3(0, 0, -2));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_SPACE) && this->quitInterface == NULL) {//DOWN
		this->camera->transform.position.y += 0.5f;
	}
	//call parent method
	this->_calculPhisics();
}

void								GameScene::drawGameObjects(void)
{
	//build Matrixs
	//this->camera->buildFPSProjection();
	if (this->current_player != NULL) {
		topoint.x = -this->current_player->transform.position.x;
		topoint.y = 0;//this->current_player->transform.position.y;
		topoint.z = -this->current_player->transform.position.z;
		this->camera->transform.position.x = topoint.x;
		this->camera->transform.position.z = topoint.z;
		//Eloignement sur x
		this->camera->transform.position.x += 25;
		//Eloignement sur y
		this->camera->transform.position.y = 35;
	}
	this->camera->buildLookAtProjection(topoint);
	//call parent method
	this->_drawGameObjects();
	//draw canvas
	if (this->interface != NULL)
		this->interface->draw();
	if (this->startGameInterface != NULL)
		this->startGameInterface->draw();
	if (this->quitInterface != NULL)
		this->quitInterface->draw();
	//reset mouse to center of screen
	//SDL_WarpMouseInWindow(BombermanClient::getInstance()->window, BombermanClient::getInstance()->screen->middleWidth, BombermanClient::getInstance()->screen->middleHeight);
}
