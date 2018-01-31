#ifndef RENDERLOOP_HPP
# define RENDERLOOP_HPP

# include "Bomberman.hpp"

# include <thread>

class RenderLoop
{
	public:

												RenderLoop( IRenderLoop * r );
												RenderLoop( RenderLoop const & src );
		virtual									~RenderLoop( void );

		RenderLoop &							operator=( RenderLoop const & rhs );
		friend std::ostream &					operator<<(std::ostream & o, RenderLoop const & i);
		void									start( void );
		void									stop( void );

	private:

		void									loopcontroller( void );
		void									looprender( void );

		bool									running;
		IRenderLoop								*renderloop;
		long									controllerRate = (long)((double) 1000000000L) / 100;
		long									renderRate = (long)((double) 1000000000L) / 60;
};

#endif
