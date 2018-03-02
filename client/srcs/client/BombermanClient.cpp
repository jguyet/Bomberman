#include "Bomberman.hpp"

// ###############################################################

// CANONICAL #####################################################

BombermanClient::BombermanClient ( void )
{
	this->current_scene = NULL;
	this->sock = NULL;
}

BombermanClient::BombermanClient ( BombermanClient const & src )
{
	*this = src;
	return ;
}

BombermanClient::~BombermanClient ( void )
{
	return ;
}

BombermanClient &			BombermanClient::operator=( BombermanClient const & rhs )
{
	return (*this);
}

std::ostream &				operator<<(std::ostream & o, BombermanClient const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						BombermanClient::initialize_properties( void )
{
	//TODO properties reader;
	this->properties = new Properties("bomberman.properties");
}

void						BombermanClient::initialize_resources( void )
{
	Loader dependenciesLoader;

	dependenciesLoader.loadShaders();
	dependenciesLoader.loadModels();
}

void						BombermanClient::build_window( void )
{
	int width, height;
	bool fullscreen;

	width = this->properties->getInt("BombermanClient.screen.width");
	height = this->properties->getInt("BombermanClient.screen.height");
	fullscreen = this->properties->getBool("BombermanClient.screen.fullscreen");

	if (width < 500 || height < 500 || width > 3000 || height > 3000) {
		printf( "Error not conform display: width:%d, height:%d\n", width, height);
		exit(0);
	}

	this->screen = new Screen(width, height, fullscreen);
	this->canvas = new Canvas(this->screen->canvas_width, this->screen->canvas_height);

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) == -1 )
    {
        printf( "Can't init SDL:  %s\n", SDL_GetError( ) );
        exit(0);
    }
	if(TTF_Init() == -1)
	{
	    printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    exit(0);
	}
	int flags = SDL_WINDOW_OPENGL;
	if (fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	this->window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screen->width, this->screen->height, flags);
	if (!this->window) {
	    printf("Couldn't create window: %s\n", SDL_GetError());
	    exit(0);
	}


	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	this->bomb = Mix_LoadWAV("./assets/sound/bombe.wav");
	this->bomb2 = Mix_LoadWAV("./assets/sound/bombe2.wav");
	this->music = Mix_LoadMUS("./assets/sound/stage1.ogg");
	this->music_menu = Mix_LoadMUS("./assets/sound/stage2.ogg");
	Mix_VolumeMusic(20);

	//OPENGL version 3.3
	//################################################
	//include this BEFORE GLFW for vao fonctionnality (for macos)
	//# if __APPLE__
	//#  define GLFW_INCLUDE_GLCOREARB
	//# endif
	//################################################
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	this->context = SDL_GL_CreateContext(this->window);
	if (!this->context) {
	    printf("Couldn't create context: %s\n", SDL_GetError());
	    exit(0);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	//0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for late swap tearing
	SDL_GL_SetSwapInterval(0);
}

void						BombermanClient::delete_inputs( void )
{
	delete KeyBoard::instance;
	delete Mouse::instance;
}

void						BombermanClient::delete_properties( void )
{
	delete this->properties;
}

void						BombermanClient::delete_resources( void )
{
	Model::deleteModels();
}

void						BombermanClient::delete_window( void )
{
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	delete this->screen;
}

void						BombermanClient::delete_fonts( void )
{
	for (std::map<std::string, TTF_Font*>::iterator it = this->fonts.begin(); it != this->fonts.end(); it++)
	{
		TTF_Font *f = it->second;
		TTF_CloseFont(f);
	}
	this->fonts.clear();
}

void						BombermanClient::setWindowSize(int newWidth, int newHeight, bool fullscreen)
{
	SDL_DestroyWindow(this->window);

	int flags = SDL_WINDOW_OPENGL;
	if (fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	this->window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, newWidth, newHeight, flags);
	SDL_GL_MakeCurrent(this->window, this->context);

	delete this->screen;
	this->screen = new Screen(newWidth, newHeight, fullscreen);
}

int	SDLCALL					input_callback_interval(void *userdata, SDL_Event* event)
{
	Mouse::handle_mousebutton(event);
	Mouse::handle_event_mousemotion(event);
	KeyBoard::key_callback(event);
	return (1);
}

void						BombermanClient::initialize_inputs( void )
{
	KeyBoard::instance = new KeyBoard();
	Mouse::instance = new Mouse();

	//asynchronous events
	SDL_AddEventWatch(input_callback_interval, NULL);
}

bool						BombermanClient::new_socket( std::string const &ip, int port )
{
	this->delete_socket();
	this->sock = new Socket(ip.c_str(), port);

	return (this->sock->state);
}

void						BombermanClient::delete_socket( void )
{
	if (this->sock != NULL) {
		if (this->sock->state == false) {
			//if sock not connected manual delete
			delete this->sock;
		} else {
			//automatique delete
			this->sock->state = false;
		}
		this->sock = NULL;
	}
}


void						BombermanClient::run( void )
{
	//start controller/render looping
	this->loop = new RenderLoop(this);

	this->loop->start();

	delete this->loop;
}

void						BombermanClient::stop( void )
{
	this->loop->stop();
}

void						BombermanClient::glfw_error_callback( int error, const char* description )
{
	fputs(description, stderr);
}

// ###############################################################

// @Override METHODS #############################################

void						BombermanClient::controllerLoop( void )//100fps
{
	Scene *scene = this->getCurrentScene<Scene>();

	if (scene != NULL) {
		scene->calculPhisics();
	}
}

void						BombermanClient::renderLoop( void )//60fps
{
	static int o = 1;
	SDL_GL_SwapWindow(this->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//fps canvas
	this->updateFps();
	this->canvas->draw();

	Scene *scene = this->getCurrentScene<Scene>();

	if (scene != NULL) {
		scene->drawGameObjects();
	}

	while(SDL_PollEvent(&this->event))
	{
		if(this->event.type == SDL_QUIT)
		{
			this->stop();
			break ;
		}
	}
}

void						BombermanClient::updateFps( void )
{
	static long lastTime = 0;
	static int fpsCount = 0;
	static int fps = 0;

	if (lastTime == 0 || TimeUtils::getCurrentSystemMillis() > (long)(lastTime + 1000)) {
		lastTime = TimeUtils::getCurrentSystemMillis();
		fps = fpsCount;
		fpsCount = 0;
		Text *t = new Text((std::ostringstream() << "FPS : " << fps).str(), "color:#ffffff;font-size:25px;font-family:arial;float:right;");
		t->transform.position.x = -115;
		t->transform.position.y = 0;
		this->canvas->addText("fps", t);
	}

	fpsCount++;
}

// ###############################################################

// EXTERNAL ######################################################

int main(void)
{
	BombermanClient *client = BombermanClient::getInstance();

	client->initialize_properties();
	client->build_window();
	client->initialize_resources();
	client->initialize_inputs();


	client->setCurrentScene<MainMenuScene>(new MainMenuScene());

	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
	printf("Supported GLSL Shaders version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

	client->run();

	client->delete_inputs();
	client->delete_resources();
	client->delete_fonts();
	client->delete_properties();
	client->delete_window();
	delete client;
	return (0);
}

// ###############################################################
