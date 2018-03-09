#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

CreditInterface::CreditInterface ( void ) : UIInterface("themes/CreditInterface.html")
{
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->canvas_width, BombermanClient::getInstance()->screen->canvas_height);
	this->canvas->setElementsMap(&this->elements);
	return ;
}

CreditInterface::CreditInterface ( CreditInterface const & src ) : UIInterface("unknow")
{
	*this = src;
	return ;
}

CreditInterface &				CreditInterface::operator=( CreditInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

CreditInterface::~CreditInterface ( void )
{
	delete this->canvas;
	return ;
}

std::ostream &				operator<<(std::ostream & o, CreditInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void					CreditInterface::draw(void)
{
	this->build();
	if (this->modified == true) {
		this->canvas->setElementsMap(&this->elements);
	}
	this->canvas->draw();
}

// ###############################################################
