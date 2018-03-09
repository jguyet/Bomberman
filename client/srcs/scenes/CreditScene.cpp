#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

CreditScene::CreditScene ( void )
{
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height, 0.1f, 1000000.0f);
	this->camera->transform.position = glm::vec3(-3.4917f,36.6297f,-17.5657f);
	this->camera->transform.rotation = glm::vec3(78.0803f,269.888f,0);
	this->camera->buildFPSProjection();

	this->interface = new CreditInterface();

	KeyBoard::instance->addHandler("CreditScene", this);
	return ;
}

CreditScene::CreditScene ( CreditScene const & src )
{
	*this = src;
	return ;
}

CreditScene &				CreditScene::operator=( CreditScene const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

CreditScene::~CreditScene ( void )
{
	KeyBoard::instance->removeHandler("CreditScene");
	if (this->interface != NULL) {
		delete this->interface;
	}
	return ;
}

std::ostream &				operator<<(std::ostream & o, CreditScene const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						CreditScene::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_ESCAPE || key == SDL_SCANCODE_KP_ENTER || key == SDL_SCANCODE_RETURN) {
		BombermanClient::getInstance()->SoundPlay(MENU_ENTER);
		BombermanClient::getInstance()->setCurrentScene<MainMenuScene>(new MainMenuScene());
	}
}

void						CreditScene::calculPhisics(void)
{
	//call parent method
	this->_calculPhisics();
}

void						CreditScene::drawGameObjects(void)
{
	this->camera->buildFPSProjection();
	//call parent method
	this->_drawGameObjects();
	//draw canvas
	if (this->interface != NULL)
		this->interface->draw();
}

// ###############################################################
