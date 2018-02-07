#include "Bomberman.hpp"

// STATIC ########################################################

BombermanClient*			BombermanClient::instance = new BombermanClient();

// ###############################################################

// CANONICAL #####################################################

BombermanClient::BombermanClient ( void )
{
	return ;
}

BombermanClient::BombermanClient ( BombermanClient const & src )
{
	*this = src;
	return ;
}

BombermanClient::~BombermanClient ( void )
{
	if (this->window) {
		glfwDestroyWindow(this->window);
	}
	glfwTerminate();
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
	ShaderUtils::instance->loadShader("simple", "./assets/shaders/Simple.vs", "./assets/shaders/Simple.fs");
	ShaderUtils::instance->loadShader("dir", "./assets/shaders/dirlightdiffambpix.vert", "./assets/shaders/dirlightdiffambpix.frag");

	Model::load("ground", ShaderUtils::instance->get("dir"), "assets/ground.obj");
	Model::load("brick", ShaderUtils::instance->get("dir"), "assets/brick.obj");
	Model::load("grass", ShaderUtils::instance->get("dir"), "assets/grass.obj");
}

void						BombermanClient::build_window( void )
{
	glfwSetErrorCallback(BombermanClient::glfw_error_callback);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//################################################
	//include this BEFORE GLFW for vao fonctionnality
	//# if __APPLE__
	//#  define GLFW_INCLUDE_GLCOREARB
	//# endif
	//################################################
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//Resizeable

	this->window = glfwCreateWindow(1680, 1050, "Bomberman", NULL, NULL);

	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->window);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glEnable(GL_MULTISAMPLE);

	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPos(this->window, 640 / 2, 480 / 2);
}

void						BombermanClient::initialize_inputs( void )
{
	// Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(this->window, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);

	KeyBoard::instance = new KeyBoard(this->window);
	Mouse::instance = new Mouse(this->window);

	glfwSetKeyCallback(this->window, KeyBoard::key_callback);
	glfwSetCursorPosCallback(this->window, Mouse::cursor_position_callback);
	glfwSetMouseButtonCallback(this->window, Mouse::mouse_button_callback);
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

	if (glfwWindowShouldClose(this->window))
		return ;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->currentController->render();
	//Swap Buffers
    glfwSwapBuffers(this->window);
	glfwPollEvents();
}

// ###############################################################

// EXTERNAL ######################################################

int main(void)
{
	//Model::loadTexturedModel("boule.obj");
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
