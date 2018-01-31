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
	//TODO obj/img loader
}

void						BombermanClient::build_window( void )
{
	glfwSetErrorCallback(BombermanClient::glfw_error_callback);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	this->window = glfwCreateWindow(640, 480, "Bomberman", NULL, NULL);

	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->window);
}

void						BombermanClient::initialize_inputs( void )
{
	Keyboard::instance = new Keyboard(this->window);
	Mouse::instance = new Mouse(this->window);

	glfwSetKeyCallback(this->window, Keyboard::key_callback);
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

void						BombermanClient::controllerLoop( void )
{
	//std::cout << "HHHH\n";
}

void						BombermanClient::renderLoop( void )
{
	if (!glfwWindowShouldClose(this->window))
	{
		float ratio;
        int width, height;
        glfwGetFramebufferSize(this->window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
	        glColor3f(1.f, 0.f, 0.f);
	        glVertex3f(-0.6f, -0.4f, 0.f);
	        glColor3f(0.f, 1.f, 0.f);
	        glVertex3f(0.6f, -0.4f, 0.f);
	        glColor3f(0.f, 0.f, 1.f);
	        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
        glfwSwapBuffers(this->window);
        glfwPollEvents();
	}
}

// ###############################################################

// EXTERNAL ######################################################

int main(void)
{
	BombermanClient *client = BombermanClient::instance;

	client->initialize_properties();
	client->initialize_resources();
	client->build_window();
	client->initialize_inputs();
	client->run();

	delete client;

	return (0);
}

// ###############################################################
