#include "Bomberman.hpp"

// STATIC ########################################################

BombermanClient*			BombermanClient::instance = new BombermanClient();

// ###############################################################

// CANONICAL #####################################################

BombermanClient::BombermanClient ( void )
{
	this->screen = new Screen(1680, 1050);
	this->canvas = new Canvas(this->screen->width, this->screen->height);

/*
	char host[] = "localhost";
	this->sock = new Socket(host, 8964);
*/
	return ;
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
}

void						BombermanClient::initialize_resources( void )
{
	//reserved for canvas
	ShaderUtils::instance->loadShader("canvas", "./assets/reserved/canvas.vert", "./assets/reserved/canvas.frag");
	Model::load("canvas", ShaderUtils::instance->get("canvas"), "assets/reserved/canvas.obj");

	//SHADERS
	ShaderUtils::instance->loadShader("dir", "./assets/shaders/global.vert", "./assets/shaders/global.frag");
	ShaderUtils::instance->loadShader("bomb", "./assets/shaders/bomb.vert", "./assets/shaders/bomb.frag");
	ShaderUtils::instance->loadShader("player", "./assets/shaders/player.vert", "./assets/shaders/player.frag");

	//Player
	Model::load("launch_bomb_anim_0", ShaderUtils::instance->get("player"), "assets/launch_bomb_anim/1.obj");
	Model::load("launch_bomb_anim_1", ShaderUtils::instance->get("player"), "assets/launch_bomb_anim/2.obj");
	Model::load("launch_bomb_anim_2", ShaderUtils::instance->get("player"), "assets/launch_bomb_anim/3.obj");

	Model::load("bomberman", ShaderUtils::instance->get("player"), "assets/bomberman_animations/test.obj");
	Model::load("bomberman2", ShaderUtils::instance->get("player"), "assets/bomberman_animations/test.obj");

	Model::load("walk_0", ShaderUtils::instance->get("player"), "assets/bomberman_animations/walk/3.obj");
	Model::load("walk_1", ShaderUtils::instance->get("player"), "assets/bomberman_animations/walk/2.obj");
	Model::load("walk_2", ShaderUtils::instance->get("player"), "assets/bomberman_animations/walk/1.obj");
	Model::load("walk_3", ShaderUtils::instance->get("player"), "assets/bomberman_animations/walk/0.obj");

	//bomb
	Model::load("bomb", ShaderUtils::instance->get("bomb"), "assets/bomb/bomb.obj");

	//textures
	Model::load("flamme_block", ShaderUtils::instance->get("dir"), "assets/textures/blocks/Flamme.obj");
	Model::load("N64", ShaderUtils::instance->get("dir"), "assets/textures/N64 Cube/N64 Cube.obj");
	Model::load("ice_block", ShaderUtils::instance->get("dir"), "assets/textures/blocks/mur1.obj");
	Model::load("ground1", ShaderUtils::instance->get("dir"), "assets/textures/blocks/sol1.obj");

	Model::load("brick", ShaderUtils::instance->get("dir"), "assets/textures/grass.obj");
	Model::load("skybox", ShaderUtils::instance->get("dir"), "assets/skybox/skybox.obj");


	Model::load("bonus-bomb-up", ShaderUtils::instance->get("dir"), "assets/textures/bonus/bomb-up.obj");
	Model::load("bonus-power-up", ShaderUtils::instance->get("dir"), "assets/textures/bonus/power-up.obj");
	Model::load("bonus-speed-up", ShaderUtils::instance->get("dir"), "assets/textures/bonus/speed-up.obj");
}

void						BombermanClient::build_window( void )
{
	if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
    {
        printf( "Can't init SDL:  %s\n", SDL_GetError( ) );
        exit(0);
    }

	if(TTF_Init() == -1)
	{
	    printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    exit(0);
	}

	this->window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screen->width, this->screen->height, SDL_WINDOW_OPENGL );
	if (!this->window) {
	    printf("Couldn't create window: %s\n", SDL_GetError());
	    exit(0);
	}

	//OPENGL version 3.3
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
	//################################################
	//include this BEFORE GLFW for vao fonctionnality (for macos)
	//# if __APPLE__
	//#  define GLFW_INCLUDE_GLCOREARB
	//# endif
	//################################################
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// // Enable depth test
	glEnable(GL_DEPTH_TEST);
	//Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	//0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for late swap tearing
	SDL_GL_SetSwapInterval(0);
}

void						BombermanClient::setWindowSize(int width, int height)
{
	SDL_SetWindowSize(this->window, width, height);
	delete this->screen;
	this->screen = new Screen(width, height);
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
	//this->currentController->process();
	this->current_scene->calculPhisics();
}

void						BombermanClient::renderLoop( void )//60fps
{
	static int o = 1;
	SDL_GL_SwapWindow(this->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//fps canvas
	this->updateFps();
	this->canvas->draw();

	//this->currentController->render();
	this->current_scene->drawGameObjects();

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
		Text *t = new Text((std::ostringstream() << "FPS : " << fps).str());
		//Text *t = new Text(2, "FPS : ", 55);
		t->transform.position.x = this->screen->width - 130;
		t->transform.position.y = 50;
		this->canvas->addText("fps", t);
	}

	fpsCount++;
}

// ###############################################################

// EXTERNAL ######################################################

int main(void)
{
	BombermanClient *client = BombermanClient::instance;

	client->build_window();
	client->initialize_properties();
	client->initialize_resources();
	client->initialize_inputs();

	//client->current_scene = new GameScene();
	client->current_scene = new MainMenuScene();

	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
	printf("Supported GLSL Shaders version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

	client->run();

	Model::deleteModels();
	delete client;
	return (0);
}

// ###############################################################
