#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

MainMenuInterface::MainMenuInterface ( void ) : UIInterface("themes/MainMenuInterface.html")
{
	this->current_position = 0;
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height);
	this->canvas->setElementsMap(&this->elements);
	KeyBoard::instance->addHandler("MainMenuInterface", this);
	return ;
}

MainMenuInterface::MainMenuInterface ( MainMenuInterface const & src ) : UIInterface("")
{
	*this = src;
	return ;
}

MainMenuInterface &				MainMenuInterface::operator=( MainMenuInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

MainMenuInterface::~MainMenuInterface ( void )
{
	KeyBoard::instance->removeHandler("MainMenuInterface");
	delete this->canvas;
	return ;
}

std::ostream &				operator<<(std::ostream & o, MainMenuInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						MainMenuInterface::draw(void)
{
	this->build();
	if (this->current_position == 0 && this->elements.count("background_solo") && this->elements.count("background_multi")) {
		this->elements["background_solo"]->setStyle("color:#FF8000");		this->elements["background_multi"]->setStyle("color:#BDBDBD");
	} else if (this->current_position == 1 && this->elements.count("background_multi") && this->elements.count("background_solo")) {
		this->elements["background_multi"]->setStyle("color:#FF8000");
		this->elements["background_solo"]->setStyle("color:#BDBDBD");
	}
	this->canvas->draw();

	if (this->elements.count("background")) {
		this->elements["background"]->transform.position.x += 0.1f;

		if (this->elements["background"]->transform.position.x > 10) {
			this->elements["background"]->transform.position.x = 0;
		}
	}
}

void						MainMenuInterface::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_UP || key == SDL_SCANCODE_DOWN) {
		this->current_position = (this->current_position + 1) % 2;
	}
}

// ###############################################################
