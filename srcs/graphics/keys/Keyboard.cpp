#include "Bomberman.hpp"

// STATIC ########################################################
KeyBoard		*KeyBoard::instance = NULL;

void			KeyBoard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "Key entry : " << key << " action : " << action << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// ###############################################################

// CANONICAL #####################################################

KeyBoard::KeyBoard ( GLFWwindow *window )
{
	this->window = window;
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

int							KeyBoard::getKey(int key)
{
	return (glfwGetKey(this->window, key));
}

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
