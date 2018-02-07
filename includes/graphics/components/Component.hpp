#ifndef COMPONENT_HPP
# define COMPONENT_HPP

class Component;

# include "Bomberman.hpp"

class Component
{
	public:
					Component( void ){};
					Component( Component const & src ){};
		virtual		~Component( void ) {};
};

#endif
