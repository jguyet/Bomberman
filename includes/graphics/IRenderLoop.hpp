#ifndef IRENDERLOOP_HPP
# define IRENDERLOOP_HPP

class IRenderLoop
{
	public:
		virtual ~IRenderLoop() {}
		virtual void controllerLoop( void ) = 0;
		virtual void renderLoop( void ) = 0;
};

#endif
