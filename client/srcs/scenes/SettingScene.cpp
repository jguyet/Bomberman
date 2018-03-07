#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

SettingScene::SettingScene ( void )
{
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::getInstance()->screen->canvas_width, BombermanClient::getInstance()->screen->canvas_height, 0.1f, 10.0f);
	this->camera->transform.position = glm::vec3(0,0,0);
	this->camera->transform.rotation = glm::vec3(0,0,0);
	this->camera->buildFPSProjection();

	this->interface = new SettingInterface();
	KeyBoard::instance->addHandler("SettingScene", this);
	return ;
}

SettingScene::SettingScene ( SettingScene const & src )
{
	*this = src;
	return ;
}

SettingScene &				SettingScene::operator=( SettingScene const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

SettingScene::~SettingScene ( void )
{
	delete this->interface;
	KeyBoard::instance->removeHandler("SettingScene");
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, SettingScene const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void								SettingScene::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_ESCAPE) {
		BombermanClient::getInstance()->SoundPlay(MENU_ENTER);
		BombermanClient::getInstance()->stop();
	}
	if (key == SDL_SCANCODE_KP_ENTER || key == SDL_SCANCODE_RETURN) {
		BombermanClient::getInstance()->SoundPlay(MENU_ENTER);
		switch(this->interface->current_position)
		{
			case 0:
			break ;
			case 1:
			break;
			case 2:
			break ;
			case 3:
			break;
			case 4:
			break;
			case 5:
				BombermanClient::getInstance()->setCurrentScene<MainMenuScene>(new MainMenuScene());
			break ;
		}
	}
}

void								SettingScene::calculPhisics(void)
{
	//call parent method
	this->_calculPhisics();
}

void								SettingScene::drawGameObjects(void)
{
	//build Matrixs
	this->camera->buildFPSProjection();
	//call parent method
	this->_drawGameObjects();

	if (this->interface != NULL) {
		this->interface->draw();
	}
}

// ###############################################################
