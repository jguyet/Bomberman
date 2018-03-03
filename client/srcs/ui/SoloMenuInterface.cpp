#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

SoloMenuInterface::SoloMenuInterface ( void ) : UIInterface("themes/SoloMenuInterface.html")
{
	this->current_position = 0;
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height);
	this->canvas->setElementsMap(&this->elements);
	KeyBoard::instance->addHandler("SoloMenuInterface", this);
	return ;
}

SoloMenuInterface::SoloMenuInterface ( SoloMenuInterface const & src ) : UIInterface("")
{
	*this = src;
	return ;
}

SoloMenuInterface &				SoloMenuInterface::operator=( SoloMenuInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

SoloMenuInterface::~SoloMenuInterface ( void )
{
	KeyBoard::instance->removeHandler("SoloMenuInterface");
	delete this->canvas;
	return ;
}

std::ostream &				operator<<(std::ostream & o, SoloMenuInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						SoloMenuInterface::draw(void)
{
	this->variables["$selected"] = (std::ostringstream() << this->current_position).str();
	this->build();
	if (this->modified == true) {
		this->canvas->setElementsMap(&this->elements);
	}
	this->canvas->draw();
}

void						SoloMenuInterface::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_UP) {
		this->current_position = (this->current_position - 1) < 0 ? 4 : (this->current_position - 1) % 5;
	}
	if (key == SDL_SCANCODE_DOWN) {
		this->current_position = (this->current_position + 1) % 5;
	}
	
}

// ###############################################################
