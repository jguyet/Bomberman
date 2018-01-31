#ifndef ICONTROLLER_HPP
# define ICONTROLLER_HPP

# include "Bomberman.hpp"

class IController
{
	public:
		virtual ~IController( void );
		virtual void process( void );
};

#endif
