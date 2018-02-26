#include "Bomberman.hpp"
#include "network/Socket.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

MainMenuScene::MainMenuScene ( void )
{
	//CAMERA
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height, 0.1f, 10.0f);
	this->camera->transform.position = glm::vec3(0,0,0);
	this->camera->transform.rotation = glm::vec3(0,0,0);
	this->camera->buildFPSProjection();

	this->interface = new MainMenuInterface();
	Mix_PlayMusic(BombermanClient::getInstance()->music_menu, 1);
	return ;
}

MainMenuScene::MainMenuScene ( MainMenuScene const & src )
{
	*this = src;
	return ;
}

MainMenuScene &				MainMenuScene::operator=( MainMenuScene const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

MainMenuScene::~MainMenuScene ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, MainMenuScene const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

void								MainMenuScene::calculPhisics(void)
{
	if (KeyBoard::instance->getKey(SDL_SCANCODE_ESCAPE)) {//ESC
		BombermanClient::getInstance()->stop();
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_KP_ENTER) || KeyBoard::instance->getKey(SDL_SCANCODE_RETURN)) {//ESC
		//BombermanClient::getInstance()->current_scene = new GameScene("map_01");


		char host[] = "localhost";
		BombermanClient::getInstance()->sock = new Socket(host, 8964);
		BombermanClient::getInstance()->current_scene = new GameScene("map_01");

		return ;
	}
	//call parent method
	this->_calculPhisics();
}

void								MainMenuScene::drawGameObjects(void)
{
	//build Matrixs
	this->camera->buildFPSProjection();
	//call parent method
	this->_drawGameObjects();
	//draw canvas
	this->interface->draw();
}
