#ifndef COMPONENT_HPP
# define COMPONENT_HPP

class Component;
class GameObject;

# include "Bomberman.hpp"

class Component
{
	public:
					Component( void ){};
					Component( Component const & src ){};
		virtual		~Component( void ) {};

	GameObject		*gameObject;
};

#endif
