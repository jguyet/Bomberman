#include "Bomberman.hpp"
#include "managers/SaveManager.hpp"

// ###############################################################

// CANONICAL #####################################################

BombermanClient::BombermanClient ( void )
{
	this->current_scene = NULL;
	this->sock = NULL;
	this->saveManager = new SaveManager();
	this->wait_changing_scene = false;
	this->waitThreads[0] = false;
	this->waitThreads[1] = false;
}

BombermanClient::BombermanClient ( BombermanClient const & src )
{
	*this = src;
	return ;
}

BombermanClient::~BombermanClient ( void )
{
	delete this->saveManager;
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
	this->enableSound = this->properties->getBool("BombermanClient.enableSound");
	this->enableMusic = this->properties->getBool("BombermanClient.enableMusic");

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

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
	    printf("Mix_OpenAudio: %s\n", Mix_GetError());
	    this->enableSound = false;
	}

	this->bomb1 = Mix_LoadWAV("./assets/sound/bomb1.wav");
	this->bomb2 = Mix_LoadWAV("./assets/sound/bomb2.wav");
	this->bomb3 = Mix_LoadWAV("./assets/sound/bomb3.wav");
	this->bomb4 = Mix_LoadWAV("./assets/sound/bomb4.wav");

	this->menu_enter = Mix_LoadWAV("./assets/sound/DONE.WAV");
	this->menu_move = Mix_LoadWAV("./assets/sound/BUTT.WAV");

	this->music = Mix_LoadMUS("./assets/sound/stage1.ogg");
	this->music_menu = Mix_LoadMUS("./assets/sound/stage2.ogg");

	// shit is getting my ears bleeding
	Mix_VolumeMusic(30);

	//OPENGL version 3.3
	//################################################
	//include this BEFORE GLFW for vao fonctionnality (for macos)
	//# if __APPLE__
	//#  define GLFW_INCLUDE_GLCOREARB
	//# endif
	//################################################
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
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

	BombermanClient::getInstance()->MusicPlay(MENU);
}

void BombermanClient::SoundPlay(Sound toPlay) {
	if (!this->enableSound)
		return ;
	Mix_Chunk *sound = NULL;
	if (toPlay == BOMB_EXPLODE) {
		int r = (rand() % 4) + 1;
		if (r == 1)
			sound = this->bomb1;
		else if (r==2)
			sound = this->bomb2;
		else if (r==3)
			sound = this->bomb3;
		else if (r==4)
			sound = this->bomb4;
	}
	if (toPlay == MENU_ENTER)
		sound = this->menu_enter;
	if (toPlay == MENU_MOVE)
		sound = this->menu_move;
	if (sound)
	{
		Mix_VolumeChunk(sound, MIX_MAX_VOLUME/2);
		if(Mix_PlayChannel(-1, sound, 0)==-1) {
			printf("Mix_PlayChannel: %s\n",Mix_GetError());
		}
	}
}

void BombermanClient::MusicPlay(Music toPlay)
{
	if (!this->enableMusic)
		return ;
	Mix_Music *music = NULL;

	if (toPlay == MENU)
		music = this->music_menu;
	if (toPlay == STAGE1)
		music = this->music;

	if (music)
	{
		if (Mix_PlayMusic(music, 1) == -1) {
			printf("Mix_PlayMusic: %s\n",Mix_GetError());
		}
	}
}

void BombermanClient::MusicStop(void)
{
	Mix_FadeOutMusic(500);
	//Mix_HaltMusic();
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

	while (this->wait_changing_scene) {
		this->waitThreads[0] = true;
		usleep(10);
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

	if (this->wait_changing_scene) {
		while (this->wait_changing_scene && this->waitThreads[0] == false) {
			usleep(10);
		}
		if (this->current_scene != NULL) {
			delete this->current_scene;
		}
		this->current_scene = this->new_scene;
		this->wait_changing_scene = false;
		this->waitThreads[0] = false;
		this->waitThreads[1] = false;
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
