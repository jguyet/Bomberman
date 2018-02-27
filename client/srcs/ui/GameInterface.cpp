#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

GameInterface::GameInterface ( int number_of_player ) : UIInterface("unknow")
{
	this->number_of_player = number_of_player;
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height);
	this->canvas->setElementsMap(&this->elements);
	return ;
}

GameInterface::GameInterface ( GameInterface const & src ) : UIInterface("")
{
	*this = src;
	return ;
}

GameInterface &				GameInterface::operator=( GameInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameInterface::~GameInterface ( void )
{
	delete this->canvas;
	return ;
}

std::ostream &				operator<<(std::ostream & o, GameInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						GameInterface::draw(void)
{
	this->debug();
	this->canvas->draw();
}

// ###############################################################
