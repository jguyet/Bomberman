#include "Bomberman.hpp"

// STATIC ########################################################
Mouse					*Mouse::instance = NULL;

void 					Mouse::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Mouse::instance->lastPosition.x = Mouse::instance->position.x;
	Mouse::instance->lastPosition.y = Mouse::instance->position.y;
	Mouse::instance->position.x = xpos;
	Mouse::instance->position.y = ypos;
	if (Mouse::instance->lastPosition.x == 0 && Mouse::instance->lastPosition.y == 0) {
		return ;
	}
	if (BombermanClient::instance->currentController->loaded == false)
		return ;
	BombermanClient::instance->currentController->camera->MouseMove(Mouse::instance->lastPosition, Mouse::instance->position);
}

void					Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    std::cout << "Mouse entry : " << button << " action : " << action << std::endl;
	Mouse::instance->pressedButton[button] = (action == PRESS || action == REPEAT) ? true : false;
}


// ###############################################################

// CANONICAL #####################################################

Mouse::Mouse ( GLFWwindow *window )
{
	this->window = window;
	this->lastPosition = glm::vec3(0,0,0);
	this->position = glm::vec3(0,0,0);
	for (int i = 0; i < 8; i++) {
		this->pressedButton[i] = false;
	}
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

void						Mouse::process(IController *controller)
{
	for (int i = 0; i < 8; i++) {
		if (this->pressedButton[i] == true) {
			controller->pressMouseButton(i);
		}
	}
}

// ###############################################################
