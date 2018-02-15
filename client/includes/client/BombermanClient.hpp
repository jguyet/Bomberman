#ifndef BOMBERMANCLIENT_HPP
# define BOMBERMANCLIENT_HPP

# include "Bomberman.hpp"

struct Screen {
	public:
		Screen(unsigned int w, unsigned int h) {
			this->width = w;
			this->height = h;
			this->middleWidth = w / 2;
			this->middleHeight = h / 2;
		}
		unsigned int width;
		unsigned int height;
		unsigned int middleWidth;
		unsigned int middleHeight;
};

class BombermanClient : public IRenderLoop
{
	public:
		// STATICS #############################################################
		static BombermanClient						*instance;
		static void									glfw_error_callback( int error, const char* description );
		// #####################################################################
		// CANONICAL ###########################################################
													BombermanClient( void );
													BombermanClient( BombermanClient const & src );
		virtual										~BombermanClient( void );
		BombermanClient &							operator=( BombermanClient const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, BombermanClient const & i);
		// #####################################################################
		// @OVERRIDE ###########################################################
		void										controllerLoop( void );
		void										renderLoop( void );
		// #####################################################################
		// PUBLIC ##############################################################
		void										initialize_properties( void );
		void										initialize_resources( void );
		void										initialize_inputs( void );
		void										build_window( void );
		void										run( void );
		void										stop( void );

		//sdl dependencies
		SDL_Window									*window;
		SDL_GLContext								context;
		SDL_Renderer								*renderer;
		SDL_Event									event;

		Scene										*current_scene;

		Screen										*screen;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		void										updateFps( void );
		RenderLoop									*loop;
		Canvas										*canvas;
		// #####################################################################
};

#endif
