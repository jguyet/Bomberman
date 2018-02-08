#include "Bomberman.hpp"

// STATIC ########################################################
KeyBoard		*KeyBoard::instance = NULL;

void			KeyBoard::key_callback(SDL_Event *event)
{
	if (event->type != SDL_KEYDOWN && event->type != SDL_KEYUP)
		return ;
	std::cout << "Key entry : " << event->key.keysym.scancode << std::endl;
	KeyBoard::instance->pressedKeys[event->key.keysym.scancode] = (event->type == SDL_KEYDOWN) ? true : false;
}

// ###############################################################

// CANONICAL #####################################################

KeyBoard::KeyBoard ( void )
{
	for (int i = 0; i < 301; i++) {
		this->pressedKeys[i] = false;
	}
	return ;
}

KeyBoard::KeyBoard ( KeyBoard const & src )
{
	*this = src;
	return ;
}

KeyBoard &				KeyBoard::operator=( KeyBoard const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

KeyBoard::~KeyBoard ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, KeyBoard const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

bool						KeyBoard::getKey(unsigned int key)
{
	return (this->pressedKeys[key]);
}

void						KeyBoard::process( IController *controller )
{
	for (int i = 0; i < 301; i++) {
		if (this->pressedKeys[i] == true) {
			controller->pressKeyBoard(i);
		}
	}
}

// ###############################################################
