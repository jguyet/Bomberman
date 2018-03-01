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
		static BombermanClient						*getInstance() {
			static BombermanClient *client = NULL;
			if (!client) {
				client = new BombermanClient();
			}
			return client;
		}

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

		void										delete_inputs( void );
		void										delete_properties( void );
		void										delete_resources( void );
		void										delete_window( void );
		void										delete_fonts( void );

		void										run( void );
		void										stop( void );

		void										setWindowSize(int width, int height);
		bool 										InitOpenAL();
		void 										ShutdownOpenAL();


		//sdl dependencies
		SDL_Window									*window;
		SDL_GLContext								context;
		SDL_Renderer								*renderer;
		SDL_Event									event;

		Scene										*current_scene;
		Screen										*screen;
		Socket 										*sock;
		Properties									*properties;


		//sound
		Mix_Music *music;
		Mix_Music *music_menu;
		Mix_Chunk *bomb;
		Mix_Chunk *bomb2;

		std::map<std::string, TTF_Font*>			fonts;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		void										updateFps( void );
		RenderLoop									*loop;
		Canvas										*canvas;

		//InitOpenAL

		ALCdevice									*Device;
		ALCcontext									*Context;

		// #####################################################################
};

#endif
