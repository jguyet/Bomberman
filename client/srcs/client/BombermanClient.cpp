#include "Bomberman.hpp"

// STATIC ########################################################

BombermanClient*			BombermanClient::instance = new BombermanClient();

// ###############################################################

// CANONICAL #####################################################

BombermanClient::BombermanClient ( void )
{
	this->screen = new Screen(1280, 720);
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
	Properties *test = new Properties("test.properties");
	//std::cout << test->get("salut") << std::endl;
	delete test;
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
	Model::load("skybox", ShaderUtils::instance->get("dir"), "assets/skybox/skybox2.obj");


	Model::load("bonus-bomb-up", ShaderUtils::instance->get("dir"), "assets/textures/bonus/bomb-up.obj");
	Model::load("bonus-power-up", ShaderUtils::instance->get("dir"), "assets/textures/bonus/power-up.obj");
	Model::load("bonus-speed-up", ShaderUtils::instance->get("dir"), "assets/textures/bonus/speed-up.obj");
}

void						BombermanClient::build_window( void )
{
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1 )
    {
        printf( "Can't init SDL:  %s\n", SDL_GetError( ) );
        exit(0);
    }

	if(TTF_Init() == -1)
	{
	    printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    exit(0);
	}

	if (Mix_Init(MIX_INIT_MP3)) {
        printf("Mix_Init: %s\n", Mix_GetError());
    }



	this->window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screen->width, this->screen->height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP );
	if (!this->window) {
	    printf("Couldn't create window: %s\n", SDL_GetError());
	    exit(0);
	}

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

	this->bomb = Mix_LoadWAV("./assets/sound/bombe.wav");
	this->bomb2 = Mix_LoadWAV("./assets/sound/bombe2.wav");
	this->music = Mix_LoadMUS("./assets/sound/stage2.mp3");
	this->music_menu = Mix_LoadMUS("./assets/sound/stage1.mp3");

	Mix_VolumeMusic(20);
    

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
		Text *t = new Text((std::ostringstream() << "FPS : " << fps).str(), "color:#ffffff;font-size:25px;float:right;");
		//Text *t = new Text(2, "FPS : ", 55);
		t->transform.position.x = -110;
		t->transform.position.y = 0;
		this->canvas->addText("fps", t);
	}

	fpsCount++;
}

// ###############################################################

/*
bool BombermanClient::InitOpenAL()
{
    // Ouverture du device
    this->Device = alcOpenDevice(NULL);
    if (!this->Device)
        return false;

    // Création du contexte
    this->Context = alcCreateContext(this->Device, NULL);
    if (!this->Context)
        return false;

    // Activation du contexte
    if (!alcMakeContextCurrent(this->Context))
        return false;

    return true;
}

void BombermanClient::ShutdownOpenAL()
{
    // Désactivation du contexte
    alcMakeContextCurrent(NULL);

    // Destruction du contexte
    alcDestroyContext(this->Context);

    // Fermeture du device
    alcCloseDevice(this->Device);
}

// EXTERNAL ######################################################

ALuint LoadSound(const std::string& Filename)
{
    // Ouverture du fichier audio avec libsndfile
    SF_INFO FileInfos;
    SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
    if (!File)
        return 0;
	// Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
    ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
    ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

	std::vector<ALshort> Samples(NbSamples);
    if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
    	return 0;
	sf_close(File);

	ALenum Format;
	switch (FileInfos.channels)
	{
		case 1 :  Format = AL_FORMAT_MONO16;   break;
		case 2 :  Format = AL_FORMAT_STEREO16; break;
		default : return 0;
	}

	ALuint Buffer;
 	alGenBuffers(1, &Buffer);
	alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

    // Vérification des erreurs
	if (alGetError() != AL_NO_ERROR)
		return 0;

	return Buffer;
}
*/
int main(void)
{
	BombermanClient *client = BombermanClient::instance;



	client->build_window();
	client->initialize_properties();
	client->initialize_resources();
	client->initialize_inputs();

	//client->InitOpenAL();
	/*
	ALuint Buffer = LoadSound("./assets/sound/bombe.wav");
	ALuint Source;
	alGenSources(1, &Source);
	alSourcei(Source, AL_BUFFER, Buffer);
	alSourcePlay(Source);
	*/

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
