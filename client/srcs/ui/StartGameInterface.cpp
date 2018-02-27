#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

StartGameInterface::StartGameInterface ( void ) : UIInterface("themes/StartGameInterface.html")
{
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height);
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
	this->canvas->draw();
}

// ###############################################################
