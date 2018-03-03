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

	this->loadCurrentLevel();
	BombermanClient::getInstance()->sock = new Socket("", 0);
	this->interface = new SoloMenuInterface();
	Mix_PlayMusic(BombermanClient::getInstance()->music_menu, 1);

	KeyBoard::instance->addHandler("SoloMenuScene", this);
}

SoloMenuScene::SoloMenuScene ( SoloMenuScene const & src )
{
	*this = src;
	return ;
}

SoloMenuScene &				SoloMenuScene::operator=( SoloMenuScene const & rhs )
{
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

void								SoloMenuScene::loadCurrentLevel()
{
	SaveObject *save = BombermanClient::getInstance()->saveManager->saveObject;
	if (save != NULL) {
		std::string level(save->map_name);
		if (level == "map_01")
			this->current_level = 1;
		else if (level == "map_02")
			this->current_level = 2;
		else if (level == "map_03")
			this->current_level = 3;
		else if (level == "map_04")
			this->current_level = 4;
	} else {
		this->current_level = 1;
	}
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
				BombermanClient::getInstance()->setCurrentScene<GameScene>(new GameScene("map_01"));
			break ;
			case 1:
				BombermanClient::getInstance()->setCurrentScene<GameScene>(new GameScene("map_02"));
			break;
			case 2:
				BombermanClient::getInstance()->setCurrentScene<GameScene>(new GameScene("map_03"));
			break ;
			case 3:
				BombermanClient::getInstance()->setCurrentScene<GameScene>(new GameScene("map_04"));
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
