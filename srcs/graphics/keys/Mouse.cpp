#include "Bomberman.hpp"

// STATIC ########################################################
Mouse					*Mouse::instance = NULL;

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

void 					Mouse::handle_event_mousemotion(SDL_Event *event)
{
	if (event->type != SDL_MOUSEMOTION)
		return ;
	float mw = BombermanClient::instance->screen->middleWidth;
	float mh = BombermanClient::instance->screen->middleHeight;
	Mouse::instance->lastPosition.x = Mouse::instance->position.x;
	Mouse::instance->lastPosition.y = Mouse::instance->position.y;
	Mouse::instance->position.x = -(event->motion.x - mw);
	Mouse::instance->position.y = -(event->motion.y - mh);
	if (Mouse::instance->lastPosition.x == 0 && Mouse::instance->lastPosition.y == 0) {
		return ;
	}
	if (BombermanClient::instance->currentController->loaded == false)
		return ;
	BombermanClient::instance->currentController->camera->MouseMove(Mouse::instance->lastPosition, Mouse::instance->position);
}

void					Mouse::handle_mousebutton(SDL_Event *event)
{
	if (event->type != SDL_MOUSEBUTTONDOWN && event->type != SDL_MOUSEBUTTONUP)
		return ;
	Mouse::instance->pressedButton[event->button.button] = (event->type == SDL_MOUSEBUTTONDOWN) ? true : false;
}

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
