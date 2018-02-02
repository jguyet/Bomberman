#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Camera::Camera ( void )
{
	this->position = new glm::vec3(0, 0, 0);
	this->direction = new glm::vec3(0, 0, 0);
	this->rotation = new glm::vec3(0, 0, 0);
	return ;
}

Camera::Camera (glm::vec3 *position, glm::vec3 *rotation)
{
	this->position = position;
	this->rotation = rotation;
	this->direction = new glm::vec3(0, 0, 0);
}

Camera::Camera ( Camera const & src )
{
	*this = src;
	return ;
}

Camera &					Camera::operator=( Camera const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Camera::~Camera ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Camera const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Camera::translate(float x, float y, float z)
{
	this->position->x += x;
	this->position->y += y;
	this->position->z += z;
}

void						Camera::setPosition(float x, float y, float z)
{
	this->position->x = x;
	this->position->y = y;
	this->position->z = z;
}

glm::vec3					*Camera::getPosition( void )
{
	return (this->position);
}

void						Camera::setDirection(float x, float y, float z)
{
	this->direction->x = x;
	this->direction->y = y;
	this->direction->z = z;
}

glm::vec3					*Camera::getDirection( void )
{
	return (this->direction);
}

glm::vec3					*Camera::getRotation( void )
{
	return (this->rotation);
}

void						Camera::setRotation(float x, float y, float z)
{
	this->rotation->x = x;
	this->rotation->y = y;
	this->rotation->z = z;
}

// ###############################################################
