#include "Bomberman.hpp"

// STATIC ########################################################
KeyBoard		*KeyBoard::instance = NULL;

void			KeyBoard::key_callback(SDL_Event *event)
{
	if (event->type != SDL_KEYDOWN && event->type != SDL_KEYUP)
		return ;
	KeyBoard::instance->pressedKeys[event->key.keysym.scancode] = (event->type == SDL_KEYDOWN) ? true : false;

	KeyBoard::instance->mutex.lock();
	std::map<const char*, KeyBoardEventHandler*> cpy = std::map<const char*, KeyBoardEventHandler*>(KeyBoard::instance->handlers);
	KeyBoard::instance->mutex.unlock();
	for (std::map<const char*, KeyBoardEventHandler*>::iterator it = cpy.begin(); it != cpy.end(); it++) {
		if (event->type == SDL_KEYUP) {
			it->second->handleUP(event->key.keysym.scancode);
		}
		if (event->type == SDL_KEYDOWN) {
			it->second->handleDOWN(event->key.keysym.scancode);
		}
	}
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

void						KeyBoard::addHandler(const char *key, KeyBoardEventHandler *handler)
{
	std::lock_guard<std::mutex> lock(this->mutex);
	this->handlers[key] = handler;
}

void						KeyBoard::removeHandler(const char *key)
{
	std::lock_guard<std::mutex> lock(this->mutex);
	if (this->handlers.count(key) == 0)
		return ;
	this->handlers.erase(key);
}

// ###############################################################
