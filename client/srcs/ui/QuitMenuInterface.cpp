#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

QuitMenuInterface::QuitMenuInterface ( void ) : UIInterface("themes/QuitMenuInterface.html")
{
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height);
	this->canvas->setElementsMap(&this->elements);
	KeyBoard::instance->addHandler("QuitMenuInterface", this);
	return ;
}

QuitMenuInterface::QuitMenuInterface ( QuitMenuInterface const & src ) : UIInterface("unknow")
{
	*this = src;
	return ;
}

QuitMenuInterface &				QuitMenuInterface::operator=( QuitMenuInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

QuitMenuInterface::~QuitMenuInterface ( void )
{
	KeyBoard::instance->removeHandler("QuitMenuInterface");
	delete this->canvas;
	return ;
}

std::ostream &				operator<<(std::ostream & o, QuitMenuInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						QuitMenuInterface::draw(void)
{
	this->build();
	this->canvas->draw();
}

void						QuitMenuInterface::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_RETURN) {
		BombermanClient::getInstance()->stop();
		//this->current_position = (this->current_position - 1) < 0 ? 3 : (this->current_position - 1) % 4;
	}
	if (key == SDL_SCANCODE_UP) {
		//this->current_position = (this->current_position - 1) < 0 ? 3 : (this->current_position - 1) % 4;
	}
	if (key == SDL_SCANCODE_DOWN) {
		//this->current_position = (this->current_position + 1) % 4;
	}
}

// ###############################################################
