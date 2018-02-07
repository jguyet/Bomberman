#include "Bomberman.hpp"

// STATIC ########################################################
KeyBoard		*KeyBoard::instance = NULL;

void			KeyBoard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "Key entry : " << key << " action : " << action << std::endl;
	KeyBoard::instance->pressedKeys[key] = (action == PRESS || action == REPEAT) ? true : false;
}

// ###############################################################

// CANONICAL #####################################################

KeyBoard::KeyBoard ( GLFWwindow *window )
{
	this->window = window;
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
