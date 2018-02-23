#include "Bomberman.hpp"

// CANONICAL #####################################################

GameScene::GameScene (std::string selected_map)
{
	//CAMERA
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::instance->screen->width, BombermanClient::instance->screen->height, 0.1f, 1000000.0f);
	this->camera->transform.position = glm::vec3(-3.4917f,36.6297f,-17.5657f);
	this->camera->transform.rotation = glm::vec3(78.0803f,269.888f,0);
	this->camera->buildFPSProjection();

	MapManager mapManager(this);
	this->map = mapManager.getMap(selected_map);
	mapManager.buildObjects(this->map);

	this->current_player = NULL;
	// BombermanClient::instance::current_scene;

	// GameObject *player = Factory::newPlayer(100);
	// this->all_player.push_back(player);
	// player->transform.position = glm::vec3(2,1,36);
	// player->transform.scale = glm::vec3(3,3,3);
	// player->transform.rotation = glm::vec3(0,0,0);
	// this->add(player);//add on scene

	//add LOGO WESH
	/*GameObject *logo_N = new GameObject();
	logo_N->AddComponent<Model>(Model::model["N64"]);
	logo_N->transform.position = glm::vec3(30,-5,0);
	logo_N->transform.scale = glm::vec3(1,1,1);
	logo_N->transform.rotation = glm::vec3(0,0,0);
	this->add(logo_N);//add on scene*/

	this->interface = new GameInterface(1);

	//SDL_ShowCursor(SDL_DISABLE);
	//SDL_SetWindowGrab(BombermanClient::instance->window, SDL_TRUE);
	return ;
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
	return ;
}

std::ostream &				operator<<(std::ostream & o, GameScene const & i)
{
	(void)i;
	return (o);
}

// ###############################################################


void								GameScene::calculPhisics(void)
{
	if (KeyBoard::instance->getKey(SDL_SCANCODE_ESCAPE)) {//ESC
		BombermanClient::instance->stop();
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_W)) {//UP
		this->camera->move(glm::vec3(0, 0, 2));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_D)) {//RIGHT
		this->camera->move(glm::vec3(2, 0, 0));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_A)) {//LEFT
		this->camera->move(glm::vec3(-2, 0, 0));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_S)) {//DOWN
		this->camera->move(glm::vec3(0, 0, -2));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_SPACE)) {//DOWN
		this->camera->transform.position.y += 0.5f;
	}
	//call parent method
	this->_calculPhisics();

	// std::cout << this->camera->transform
}

void								GameScene::drawGameObjects(void)
{
	//build Matrixs
	//this->camera->buildFPSProjection();
	this->camera->buildLookAtProjection(glm::vec3(-12.f,1,-18.f));
	//call parent method
	this->_drawGameObjects();
	//draw canvas
	this->interface->draw();
	//reset mouse to center of screen
	//SDL_WarpMouseInWindow(BombermanClient::instance->window, BombermanClient::instance->screen->middleWidth, BombermanClient::instance->screen->middleHeight);
}
