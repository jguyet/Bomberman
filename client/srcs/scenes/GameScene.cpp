#include "Bomberman.hpp"
#include "managers/MapManager.hpp"
#include "managers/SaveManager.hpp"

// CANONICAL #####################################################

GameScene::GameScene (std::string selected_map)
{
	this->current_player = NULL;
	this->startGameInterface = NULL;
	this->quitInterface = NULL;
	this->endGameInterface = NULL;

	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height, 0.1f, 1000000.0f);
	this->camera->transform.position = glm::vec3(-3.4917f,36.6297f,-17.5657f);
	this->camera->transform.rotation = glm::vec3(78.0803f,269.888f,0);
	this->camera->buildFPSProjection();

	this->mapManager = new MapManager(this, selected_map);

	this->map = this->mapManager->getMap();
	if (this->map) {
		this->mapManager->buildObjects();
		this->interface = new GameInterface(this);
		if (BombermanClient::getInstance()->sock && BombermanClient::getInstance()->sock->state == false)
		{
			BombermanClient::getInstance()->saveManager->save(this->map->name);
			this->StartSolo();
		} else {
			this->startGameInterface = new StartGameInterface();
		}
	} else {
		BombermanClient::getInstance()->setCurrentScene<MainMenuScene>(new MainMenuScene());
	}

	//if grab mouse
	//SDL_ShowCursor(SDL_DISABLE);
	//SDL_SetWindowGrab(BombermanClient::getInstance()->window, SDL_TRUE);
	KeyBoard::instance->addHandler("GameScene", this);
}

void GameScene::StartSolo(void)
{
	GameObject 				*playerObject = Factory::newPlayer(1);

	DoorManager::setRandomDoor(this);
	Case *spawn = this->mapManager->getRandomWalkableSoloCase();

	if (spawn) {
		glm::vec3 pos = spawn->position;
		playerObject->transform.scale = glm::vec3(3,3,3);
		playerObject->transform.rotation = glm::vec3(0,0,0);
		playerObject->transform.position = glm::vec3(pos.x, 1.f, pos.z);

		this->current_player = playerObject;
		this->players.push_back(playerObject);
		this->all_player.push_back(playerObject);
		this->add(playerObject);
		BombermanClient::getInstance()->MusicPlay(STAGE1);
	}

/*
	GameObject *player = Factory::newPlayer(100);
	this->all_player.push_back(player);
	this->players.push_back(player);
	player->transform.position = glm::vec3(4,1,38);
	player->transform.scale = glm::vec3(3,3,3);
	player->transform.rotation = glm::vec3(0,0,0);
	this->add(player);//add on scene
	*/
}

void					GameScene::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_KP_PLUS)
	{
		BombermanClient::getInstance()->lockCam = !BombermanClient::getInstance()->lockCam;
	}
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
	KeyBoard::instance->removeHandler("GameScene");

	if (this->current_player != NULL) {
		this->current_player = NULL;
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
	if (this->endGameInterface != NULL) {
		delete this->endGameInterface;
	}
	delete this->mapManager;
}

std::ostream &				operator<<(std::ostream & o, GameScene const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

void								GameScene::startGame(void)
{
	if (this->startGameInterface != NULL) {
		StartGameInterface *tmp = this->startGameInterface;
		this->startGameInterface = NULL;
		delete tmp;
	}
}

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

void								GameScene::openQuitInterface(void)
{
	if (KeyBoard::instance->getKey(SDL_SCANCODE_ESCAPE) && this->quitInterface == NULL) {//ESC
		this->quitInterface = new QuitMenuInterface(this);
		if (this->current_player != NULL) {
			CharacterControllerScript *script = ((CharacterControllerScript*)this->current_player->GetComponent<Script>());
			script->locked = true;
		}
	}
}

void								GameScene::openEndGameInterface(bool is_winner)
{
	this->endGameInterface = new EndGameInterface(is_winner);
}

void								GameScene::move_camera(void)
{
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
}

void								GameScene::build_camera(void)
{
	if (BombermanClient::getInstance()->lockCam)
	{
		if (this->current_player != NULL && this->map != NULL) {
			topoint.x = ((-this->current_player->transform.position.x) + -((this->map->height * 2) / 2)) / 2;
			topoint.y = 0;
			topoint.z = ((-this->current_player->transform.position.z) + -((this->map->width * 2) / 2)) / 2;
			this->camera->transform.position.x = topoint.x;
			this->camera->transform.position.z = topoint.z;
			//Eloignement sur x
			this->camera->transform.position.x += 15;
			//Eloignement sur y
			this->camera->transform.position.y = 30;
		}
		this->camera->buildLookAtProjection(topoint);
	} else {
		this->camera->buildFPSProjection();
	}
}

void								GameScene::calculPhisics(void)
{
	if (KeyBoard::instance->getKey(SDL_SCANCODE_G) && this->endGameInterface == NULL) {
		this->openEndGameInterface(true);
	}
	this->openQuitInterface();
	//call parent method
	this->_calculPhisics();
}

void								GameScene::drawGameObjects(void)
{
	this->move_camera();
	this->build_camera();
	//call parent method
	this->_drawGameObjects();
	//draw canvas
	if (this->interface != NULL)
		this->interface->draw();
	if (this->startGameInterface != NULL)
		this->startGameInterface->draw();
	if (this->endGameInterface != NULL)
		this->endGameInterface->draw();
	if (this->quitInterface != NULL)
		this->quitInterface->draw();
	//reset mouse to center of screen
	if (!BombermanClient::getInstance()->lockCam)
		SDL_WarpMouseInWindow(BombermanClient::getInstance()->window, BombermanClient::getInstance()->screen->middleWidth, BombermanClient::getInstance()->screen->middleHeight);
}
