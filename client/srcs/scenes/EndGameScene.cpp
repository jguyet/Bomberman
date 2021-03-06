#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

EndGameScene::EndGameScene ( bool is_winner )
{
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height, 0.1f, 1000000.0f);
	this->camera->transform.position = glm::vec3(-3.4917f,36.6297f,-17.5657f);
	this->camera->transform.rotation = glm::vec3(78.0803f,269.888f,0);
	this->camera->buildFPSProjection();

	this->interface = new EndGameInterface(is_winner);

	KeyBoard::instance->addHandler("EndGameScene", this);
	return ;
}

EndGameScene::EndGameScene ( EndGameScene const & src )
{
	*this = src;
	return ;
}

EndGameScene &				EndGameScene::operator=( EndGameScene const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

EndGameScene::~EndGameScene ( void )
{
	KeyBoard::instance->removeHandler("EndGameScene");

	if (this->interface != NULL) {
		delete this->interface;
	}
	return ;
}

std::ostream &				operator<<(std::ostream & o, EndGameScene const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						EndGameScene::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_KP_ENTER || key == SDL_SCANCODE_RETURN) {
		BombermanClient::getInstance()->SoundPlay(MENU_ENTER);
		switch(this->interface->current_position)
		{
			case 0:
				BombermanClient::getInstance()->setCurrentScene<SoloMenuScene>(new SoloMenuScene());
			break ;
			case 1:
				BombermanClient::getInstance()->setCurrentScene<MainMenuScene>(new MainMenuScene());
			break;
		}
		BombermanClient::getInstance()->MusicStop();
		BombermanClient::getInstance()->MusicPlay(MENU);
	}
}

void						EndGameScene::calculPhisics(void)
{
	//call parent method
	this->_calculPhisics();
}

void						EndGameScene::drawGameObjects(void)
{
	this->camera->buildFPSProjection();
	//call parent method
	this->_drawGameObjects();
	//draw canvas
	if (this->interface != NULL)
		this->interface->draw();
}
