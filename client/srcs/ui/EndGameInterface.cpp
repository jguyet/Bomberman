#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

EndGameInterface::EndGameInterface ( bool is_winner ) : UIInterface("themes/EndGameInterface.html")
{
	this->is_winner = is_winner;
	this->current_position = 0;
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->canvas_width, BombermanClient::getInstance()->screen->canvas_height);
	this->canvas->setElementsMap(&this->elements);
	KeyBoard::instance->addHandler("EndGameInterface", this);
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
	KeyBoard::instance->removeHandler("EndGameInterface");
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

void					EndGameInterface::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_UP) {
		this->current_position = (this->current_position - 1) < 0 ? 1 : (this->current_position - 1) % 2;
	}
	if (key == SDL_SCANCODE_DOWN) {
		this->current_position = (this->current_position + 1) % 2;
	}
}

void					EndGameInterface::draw(void)
{
	this->variables["$is_winner"] = (std::ostringstream() << (this->is_winner ? "true" : "false")).str();
	this->variables["$selected"] = (std::ostringstream() << this->current_position).str();

	this->build();
	if (this->modified == true) {
		this->canvas->setElementsMap(&this->elements);
	}
	this->canvas->draw();
}

// ###############################################################
