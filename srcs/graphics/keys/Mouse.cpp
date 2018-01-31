#include "Bomberman.hpp"

// STATIC ########################################################
Mouse					*Mouse::instance = NULL;

void 					Mouse::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Mouse::instance->x = xpos;
	Mouse::instance->y = ypos;
}

void					Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    std::cout << "Mouse entry : " << button << " action : " << action << std::endl;
}


// ###############################################################

// CANONICAL #####################################################

Mouse::Mouse ( GLFWwindow *window )
{
	this->window = window;
	return ;
}

Mouse::Mouse ( Mouse const & src )
{
	*this = src;
	return ;
}

Mouse &				Mouse::operator=( Mouse const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Mouse::~Mouse ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Mouse const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

int							Mouse::getMouseButton(int button)
{
	return (glfwGetMouseButton(this->window, button));
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
