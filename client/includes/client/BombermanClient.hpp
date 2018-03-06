#ifndef BOMBERMANCLIENT_HPP
# define BOMBERMANCLIENT_HPP

# include "Bomberman.hpp"

struct Screen {
	public:
		Screen(unsigned int w, unsigned int h, bool fullscreen) {
			this->width = w;
			this->height = h;
			this->middleWidth = w / 2;
			this->middleHeight = h / 2;
			this->canvas_width = 1280;
			this->canvas_height = 720;
			this->fullscreen = fullscreen;
		}
		unsigned int width;
		unsigned int height;
		unsigned int middleWidth;
		unsigned int middleHeight;
		unsigned int canvas_width;
		unsigned int canvas_height;
		bool fullscreen;
};

enum Sound {
	BOMB_EXPLODE,
	BOMB_DROP,
	MENU_MOVE,
	MENU_ENTER,
	DIE,
	WIN,
	LOOSE
};

enum Music {
	MENU,
	STAGE1
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

		template <typename T> T						*getCurrentScene(void);
		template <typename T> T						*setCurrentScene(Scene *scene);

		bool										new_socket( std::string const &ip, int port );
		void										delete_socket( void );
		void 										SoundPlay(Sound toPlay);
		void 										MusicPlay(Music toPlay);

		void										setWindowSize(int newWidth, int newHeight, bool fullscreen);

		void										run( void );
		void										stop( void );

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

		bool 										enableSound = 0;
		bool 										enableMusic = 0;

		//sound
		Mix_Music 									*music      = NULL;
		Mix_Music 									*music_menu = NULL;
		Mix_Chunk 									*bomb       = NULL;
		Mix_Chunk 									*bomb2      = NULL;
		Mix_Chunk									*menu_enter = NULL;

		bool 										lockCam = true;

		std::map<std::string, TTF_Font*>			fonts;

		//managers
		SaveManager									*saveManager;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		void										updateFps( void );
		RenderLoop									*loop;
		Canvas										*canvas;

		std::mutex									mutex;

		bool										wait_changing_scene;
		bool										waitThreads[2];
		Scene										*new_scene;
		// #####################################################################
};

template <typename T>
T							*BombermanClient::getCurrentScene( void )
{
	std::lock_guard<std::mutex> lock(this->mutex);
	if (this->current_scene == NULL)
		return NULL;
	return dynamic_cast<T*>(this->current_scene);
}

template <typename T>
T							*BombermanClient::setCurrentScene( Scene *scene )
{
	std::lock_guard<std::mutex> lock(this->mutex);
	Scene *last_scene = NULL;
	if (this->current_scene != NULL) {
		last_scene = this->current_scene;
	}
	this->new_scene = scene;
	this->wait_changing_scene = true;
	if (scene == NULL)
		return NULL;
	return dynamic_cast<T*>(scene);
}

#endif
