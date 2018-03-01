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
	this->variables["$selected"] = (std::ostringstream() << this->current_position).str();

	this->build();
	this->canvas->draw();
}

void						MainMenuInterface::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_UP) {
		this->current_position = (this->current_position - 1) < 0 ? 4 : (this->current_position - 1) % 5;
	}
	if (key == SDL_SCANCODE_DOWN) {
		this->current_position = (this->current_position + 1) % 5;
	}
}

// ###############################################################
