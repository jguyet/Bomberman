#include "Bomberman.hpp"

// STATIC ########################################################

BombermanClient*			BombermanClient::instance = new BombermanClient();

// ###############################################################

// CANONICAL #####################################################

BombermanClient::BombermanClient ( void )
{
	this->screen = new Screen(1680, 1050);
	this->canvas = new Canvas(this->screen->width, this->screen->height);
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
	if (this != &rhs)
	{
		// make stuff
	}
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
	//SHADERS
	ShaderUtils::instance->loadShader("simple", "./assets/shaders/Simple.vs", "./assets/shaders/Simple.fs");
	ShaderUtils::instance->loadShader("dir", "./assets/shaders/dirlightdiffambpix.vert", "./assets/shaders/dirlightdiffambpix.frag");
	ShaderUtils::instance->loadShader("canvas", "./assets/shaders/canvas.vert", "./assets/shaders/canvas.frag");


	//FONTS
	this->font = TTF_OpenFont("assets/fonts/angelina.ttf", 65);

	//MODELS
	Model::load("ground", ShaderUtils::instance->get("dir"), "assets/ground.obj");
	Model::load("brick", ShaderUtils::instance->get("dir"), "assets/brick.obj");
	Model::load("grass", ShaderUtils::instance->get("dir"), "assets/grass.obj");
	Model::load("bomberman", ShaderUtils::instance->get("dir"), "assets/RedBomber/RedBomber.obj");
	//Model::load("bomberman", ShaderUtils::instance->get("dir"), "assets/WhiteBomber/WhiteBomber.obj");
	Model::load("N64", ShaderUtils::instance->get("dir"), "assets/N64 Cube/N64 Cube.obj");
	Model::load("bomb", ShaderUtils::instance->get("dir"), "assets/bomb/bomb.obj");
	Model::load("Gold", ShaderUtils::instance->get("dir"), "assets/GoldNumemon/chr113.dae");
	Model::load("canvas", ShaderUtils::instance->get("canvas"), "assets/canvas.obj");
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

	// this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// if (!this->renderer) {
	// 	printf("Couldn't create renderer: %s\n", SDL_GetError());
	// 	exit(0);
	// }

	//OPENGL version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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
    //
	// // Enable depth test
	glEnable(GL_DEPTH_TEST);
	//Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);
    //
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(this->window, SDL_TRUE);
	SDL_WarpMouseInWindow(this->window, this->screen->middleWidth, this->screen->middleHeight);
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
	this->currentController->process();
}

void						BombermanClient::renderLoop( void )//60fps
{
	static int o = 1;
	SDL_GL_SwapWindow(this->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//fps canvas
	this->updateFps();
	this->canvas->draw();

	this->currentController->render();

	while(SDL_PollEvent(&this->event))
    {
		if(this->event.type == SDL_QUIT)
	    {
	        this->stop();
			break ;
	    }
    }
	//reset mouse to center of screen
	SDL_WarpMouseInWindow(this->window, this->screen->middleWidth, this->screen->middleHeight);
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
	}
	std::ostringstream ss;
	ss << "FPS : ";
	ss << fps;
	std::string s(ss.str());
	Text *t = new Text(s.c_str());
	t->transform.position.x = this->screen->width - 130;
	t->transform.position.y = 50;
	this->canvas->addText("fps", t);

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

	client->currentController = new GameController();

	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
	printf("Supported GLSL Shaders version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

	client->run();

	Model::deleteModels();
	delete client;
	return (0);
}

// ###############################################################
