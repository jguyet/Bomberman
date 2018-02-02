#include "Bomberman.hpp"

// STATIC ########################################################

BombermanClient*			BombermanClient::instance = new BombermanClient();

// ###############################################################

// CANONICAL #####################################################

BombermanClient::BombermanClient ( void )
{
	this->transform = new Transform();
	this->camera = new Camera();
	this->transform->setCamera(this->camera);
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
	//TODO obj/img loader
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

	this->window = glfwCreateWindow(640, 480, "Bomberman", NULL, NULL);

	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->window);
}

void						BombermanClient::initialize_inputs( void )
{
	// Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

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

// HERITANCE METHODS #############################################

void						BombermanClient::controllerLoop( void )//100fps
{
	//std::cout << "HHHH\n";
}

void						BombermanClient::renderLoop( void )//60fps
{

	if (glfwWindowShouldClose(this->window))
		return ;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	//GLuint programID = ShaderUtils::loadShaders("./assets/shaders/Simple.vs", "./assets/shaders/Simple.fs");

	//glUseProgram(programID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);


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

	client->initialize_properties();
	client->initialize_resources();
	client->build_window();
	client->initialize_inputs();

	client->currentView = new SimpleView();

	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
	printf("Supported GLSL Shaders version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	//GEn vao
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	ShaderUtils::instance->loadShader("simple", "./assets/shaders/Simple.vs", "./assets/shaders/Simple.fs");
	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(ShaderUtils::instance->get("simple"), "MVP");

	glUseProgram(ShaderUtils::instance->get("simple"));

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	client->camera->setPosition(4,3,3);

	while (!glfwWindowShouldClose(client->window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(ShaderUtils::instance->get("simple"));

		client->transform->setProjection(45.0f, 4.0f, 3.0f, 0.1f, 100.0f);
		glm::mat4 MVP = client->transform->enableProjectionTransformation();

		client->camera->getPosition()->x += 0.1f;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
		   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		   3,                  // size
		   GL_FLOAT,           // type
		   GL_FALSE,           // normalized?
		   0,                  // stride
		   (void*)0            // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(client->window);
		glfwPollEvents();

		usleep(100);
	}
	//client->run();

	delete client;

	return (0);
}

// ###############################################################
