#ifndef RENDERLOOP_HPP
# define RENDERLOOP_HPP

# include "Bomberman.hpp"

# include <thread>

class RenderLoop
{
	public:
		// STATICS #############################################################
		// #####################################################################
		// CANONICAL ###########################################################
												RenderLoop( IRenderLoop * r );
												RenderLoop( RenderLoop const & src );
		virtual									~RenderLoop( void );
		RenderLoop &							operator=( RenderLoop const & rhs );
		friend std::ostream &					operator<<(std::ostream & o, RenderLoop const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		void									start( void );
		void									stop( void );
		// #####################################################################
	private:
		// PRIVATE #############################################################
		void									loopcontroller( void );
		void									looprender( void );

		bool									running;
		IRenderLoop								*renderloop;
		long									controllerRate = 1000000000L / 100L;
		long									renderRate = 1000000000L / 100L;
		// #####################################################################
};

#endif
