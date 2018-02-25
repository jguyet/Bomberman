#include "Bomberman.hpp"
#include "network/Socket.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

MainMenuScene::MainMenuScene ( void )
{
	//CAMERA
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::instance->screen->width, BombermanClient::instance->screen->height, 0.1f, 10.0f);
	this->camera->transform.position = glm::vec3(0,0,0);
	this->camera->transform.rotation = glm::vec3(0,0,0);
	this->camera->buildFPSProjection();

	this->interface = new MainMenuInterface();
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
	//BombermanClient::instance->sock->do_select();
	if (KeyBoard::instance->getKey(SDL_SCANCODE_ESCAPE)) {//ESC
		BombermanClient::instance->stop();
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_KP_ENTER) || KeyBoard::instance->getKey(SDL_SCANCODE_RETURN)) {//ESC
		//BombermanClient::instance->current_scene = new GameScene("map_01");
		BombermanClient::instance->current_scene = new GameScene("map_01");
		char host[] = "localhost";
		BombermanClient::instance->sock = new Socket(host, 8964);
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
