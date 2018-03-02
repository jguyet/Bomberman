#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

StartGameInterface::StartGameInterface ( void ) : UIInterface("themes/StartGameInterface.html")
{
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->canvas_width, BombermanClient::getInstance()->screen->canvas_height);
	this->canvas->setElementsMap(&this->elements);
	return ;
}

StartGameInterface::StartGameInterface ( StartGameInterface const & src ) : UIInterface("unknow")
{
	*this = src;
	return ;
}

StartGameInterface &				StartGameInterface::operator=( StartGameInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

StartGameInterface::~StartGameInterface ( void )
{
	delete this->canvas;
	return ;
}

std::ostream &				operator<<(std::ostream & o, StartGameInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						StartGameInterface::draw(void)
{
	this->build();
	if (this->modified == true) {
		this->canvas->setElementsMap(&this->elements);
	}
	this->canvas->draw();
}

// ###############################################################
