#include "Bomberman.hpp"

// STATIC ########################################################
Keyboard		*Keyboard::instance = NULL;

void			Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "Key entry : " << key << " action : " << action << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// ###############################################################

// CANONICAL #####################################################

Keyboard::Keyboard ( GLFWwindow *window )
{
	this->window = window;
	return ;
}

Keyboard::Keyboard ( Keyboard const & src )
{
	*this = src;
	return ;
}

Keyboard &				Keyboard::operator=( Keyboard const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Keyboard::~Keyboard ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Keyboard const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

int							Keyboard::getKey(int key)
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
