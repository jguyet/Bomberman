#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Transform::Transform ( void )
{
	this->translation = new glm::vec3(0, 0, 0);
	this->rotation = new glm::vec3(0, 0, 0);
	this->scale = new glm::vec3(1, 1, 1);
	return ;
}

Transform::Transform ( Transform const & src )
{
	*this = src;
	return ;
}

Transform &				Transform::operator=( Transform const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Transform::~Transform ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Transform const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

glm::mat4					Transform::enableProjectionTransformation( void )
{

	glm::mat4 projection = glm::perspective(glm::radians(this->fov), this->width / this->height, this->zNear, this->zFar);

	// glm::mat4 viewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(-this->camera->getPosition()->x, -this->camera->getPosition()->y, -this->camera->getPosition()->z));
	// glm::mat4 viewRotateX = glm::rotate(viewTranslate, this->camera->getRotation()->x, glm::vec3(1.0f, 0.0f, 0.0f));
	// glm::mat4 viewRotateY = glm::rotate(viewRotateY, this->camera->getRotation()->y, glm::vec3(0.0f, 1.0f, 0.0f));
	// glm::mat4 viewRotateZ = glm::rotate(viewRotateZ, this->camera->getRotation()->z, glm::vec3(0.0f, 0.0f, 1.0f));
	// glm::mat4 view = viewRotateZ;


	glm::mat4 view       = glm::lookAt(
								glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	glm::mat4 model = glm::mat4(1.0f);//glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

	glm::mat4 mvp = projection * view * model;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	// glUseProgram(programID);
	return (mvp);
}

void						Transform::setProjection(float fov, float width, float height, float zNear, float zFar)
{
	this->fov = fov;
	this->width = width;
	this->height = height;
	this->zNear = zNear;
	this->zFar = zFar;
}

glm::vec3					*Transform::getTranslation( void )
{
	return (this->translation);
}

void						Transform::setTranslation(float x, float y, float z)
{
	this->translation->x = x;
	this->translation->y = y;
	this->translation->z = z;
}

glm::vec3					*Transform::getRotation( void )
{
	return (this->translation);
}

void						Transform::setRotation(float x, float y, float z)
{
	this->rotation->x = x;
	this->rotation->y = y;
	this->rotation->z = z;
}

glm::vec3					*Transform::getScale( void )
{
	return (this->scale);
}

void						Transform::setScale(float x, float y, float z)
{
	this->scale->x = x;
	this->scale->y = y;
	this->scale->z = z;
}

Camera						*Transform::getCamera( void )
{
	return (this->camera);
}

void						Transform::setCamera(Camera *camera)
{
	this->camera = camera;
}

// ###############################################################
