#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

EndGameInterface::EndGameInterface ( bool is_winner ) : UIInterface("themes/EndGameInterface.html")
{
	this->is_winner = is_winner;
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->canvas_width, BombermanClient::getInstance()->screen->canvas_height);
	this->canvas->setElementsMap(&this->elements);
	return ;
}

EndGameInterface::EndGameInterface ( EndGameInterface const & src ) : UIInterface("unknow")
{
	*this = src;
	return ;
}

EndGameInterface &				EndGameInterface::operator=( EndGameInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

EndGameInterface::~EndGameInterface ( void )
{
	delete this->canvas;
	return ;
}

std::ostream &				operator<<(std::ostream & o, EndGameInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void					EndGameInterface::draw(void)
{
	this->build();
	if (this->modified == true) {
		this->canvas->setElementsMap(&this->elements);
	}
	this->canvas->draw();
}

// ###############################################################
