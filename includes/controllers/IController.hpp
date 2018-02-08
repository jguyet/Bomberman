#ifndef ICONTROLLER_HPP
# define ICONTROLLER_HPP

# include "Bomberman.hpp"

class IController : public Component
{
	public:

		// PROCESS METHOD 100FPS
		virtual void				process( void ) = 0;
		// RENDER METHOD 60FPS
		virtual void				render( void ) = 0;

		// ADD DEFAULT MAP FOR HOOKING INPUTS !
		// KEYBOARD EVENT
		virtual void				pressKeyBoard(unsigned int key) = 0;
		// MOUSE BUTTON EVENT
		virtual void				pressMouseButton(unsigned int button) = 0;

		// CAMERA
		Camera						*camera = NULL;
		// DEFAULT LOADING VAR
		bool						loaded = false;
};

#endif
