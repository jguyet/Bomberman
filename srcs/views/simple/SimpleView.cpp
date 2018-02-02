#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

SimpleView::SimpleView ( void )
{
	this->keyBoard_map[87] = &SimpleView::pressUp;
	this->keyBoard_map[68] = &SimpleView::pressRight;
	this->keyBoard_map[65] = &SimpleView::pressLeft;
	this->keyBoard_map[83] = &SimpleView::pressDown;

	//GEn vao
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	this->matrixID = glGetUniformLocation(ShaderUtils::instance->get("simple"), "MVP");

	glUseProgram(ShaderUtils::instance->get("simple"));

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &this->vertexBuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return ;
}

SimpleView::SimpleView ( SimpleView const & src )
{
	*this = src;
	return ;
}

SimpleView &				SimpleView::operator=( SimpleView const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

SimpleView::~SimpleView ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, SimpleView const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						SimpleView::render( void )
{
	glUseProgram(ShaderUtils::instance->get("simple"));

	BombermanClient::instance->transform->setProjection(45.0f, 16.0f, 9.0f, 0.1f, 100.0f);
	glm::mat4 MVP = BombermanClient::instance->transform->enableProjectionTransformation();

	glUniformMatrix4fv(this->matrixID, 1, GL_FALSE, &MVP[0][0]);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
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
}

void 						SimpleView::pressRight( void )
{
	BombermanClient::instance->camera->getPosition()->x += 1;
	std::cout << "Right" << std::endl;
}

void 						SimpleView::pressLeft( void )
{
	BombermanClient::instance->camera->getPosition()->x -= 1;
	std::cout << "Left" << std::endl;
}

void 						SimpleView::pressUp( void )
{
	BombermanClient::instance->camera->getPosition()->y += 1;
	std::cout << "Up" << std::endl;
}

void 						SimpleView::pressDown( void )
{
	BombermanClient::instance->camera->getPosition()->y -= 1;
	std::cout << "Down" << std::endl;
}


// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
