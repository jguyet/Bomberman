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

	this->loadCurrentLevel();
	BombermanClient::getInstance()->sock = new Socket("", 0);
	// Mix_PlayMusic(BombermanClient::getInstance()->music_menu, 1);
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
	this->interface->current_level = BombermanClient::getInstance()->saveManager->getCurrentLevel();
}

void								SoloMenuScene::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_ESCAPE) {
		BombermanClient::getInstance()->stop();
	}
	if (key == SDL_SCANCODE_KP_ENTER || key == SDL_SCANCODE_RETURN) {
		if (this->interface->current_position >= 0 && this->interface->current_position <= 3)
		{
			this->interface->current_position++;
			if (this->interface->current_level >= this->interface->current_position) {
				std::string level_name = "map_0" + std::to_string(this->interface->current_position);
				BombermanClient::getInstance()->setCurrentScene<GameScene>(new GameScene(level_name));
			}
			else {
				printf("You can't access to the stage %d, you are on the stage %d, sorry !\n", this->interface->current_position, this->interface->current_level);
			}
		} else if (this->interface->current_position == 4)
		{
			BombermanClient::getInstance()->setCurrentScene<GameScene>(new MainMenuScene());
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
