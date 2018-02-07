#ifndef IRENDERLOOP_HPP
# define IRENDERLOOP_HPP

# include "Bomberman.hpp"

class IRenderLoop
{
	public:
		//CONTROLLER LOOP 100FPS
		virtual void 	controllerLoop( void ) = 0;
		//RENDER LOOP 60FPS
		virtual void 	renderLoop( void ) = 0;
};

#endif
