#ifndef IVIEW_HPP
# define IVIEW_HPP

# include "Bomberman.hpp"

class IView
{
	public:
		virtual ~IView( void ) {}
		virtual void render( void ) = 0;
		virtual void pressKeyBoard(unsigned int key) = 0;
};

#endif
