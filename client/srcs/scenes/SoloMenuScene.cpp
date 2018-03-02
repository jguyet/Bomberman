#include "Bomberman.hpp"
#include "network/Socket.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

SoloMenuScene::SoloMenuScene ( void )
{
	//CAMERA
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height, 0.1f, 10.0f);
	this->camera->transform.position = glm::vec3(0,0,0);
	this->camera->transform.rotation = glm::vec3(0,0,0);
	this->camera->buildFPSProjection();

	this->interface = new SoloMenuInterface();
	Mix_PlayMusic(BombermanClient::getInstance()->music_menu, 1);

	KeyBoard::instance->addHandler("SoloMenuScene", this);
	return ;
}

SoloMenuScene::SoloMenuScene ( SoloMenuScene const & src )
{
	*this = src;
	return ;
}

SoloMenuScene &				SoloMenuScene::operator=( SoloMenuScene const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

SoloMenuScene::~SoloMenuScene ( void )
{
	delete this->interface;
	KeyBoard::instance->removeHandler("SoloMenuScene");
	return ;
}

std::ostream &				operator<<(std::ostream & o, SoloMenuScene const & i)
{
	(void)i;
	return (o);
}

bool								SoloMenuScene::select_local(void)
{
	if (BombermanClient::getInstance()->sock != NULL) {
		BombermanClient::getInstance()->sock->state = false;
		BombermanClient::getInstance()->sock = NULL;
	}
	BombermanClient::getInstance()->sock = new Socket("", 0);
	BombermanClient::getInstance()->setCurrentScene<GameScene>(new GameScene("map_01"));
	return true;
}

void								SoloMenuScene::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_ESCAPE) {
		BombermanClient::getInstance()->stop();
	}
	if (key == SDL_SCANCODE_KP_ENTER || key == SDL_SCANCODE_RETURN) {
		switch(this->interface->current_position)
		{
			case 0:
				this->select_local();
			break ;
			case 1:
				//this->select_server();
			break;
			case 2:
			break ;
			case 3:
			break;
			case 4:
				BombermanClient::getInstance()->setCurrentScene<GameScene>(new MainMenuScene());
			break ;
		}
	}
}

void								SoloMenuScene::calculPhisics(void)
{
	//call parent method
	this->_calculPhisics();
}

void								SoloMenuScene::drawGameObjects(void)
{
	//build Matrixs
	this->camera->buildFPSProjection();
	//call parent method
	this->_drawGameObjects();
	//draw canvas
	this->interface->draw();
}
