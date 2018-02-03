#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Camera::Camera ( void )
{
	this->position = glm::vec3(0, 0, 0);
	this->direction = glm::vec3(0, 0, 0);
	this->rotation = glm::vec3(0, 0, 0);
	this->right = glm::vec3(0, 0, 0);
	this->up = glm::vec3(0, 0, 0);
	this->UpdateView();
	return ;
}

Camera::Camera (glm::vec3 &position, glm::vec3 &rotation)
{
	this->position = position;
	this->rotation = rotation;
	this->direction = glm::vec3(0, 0, 0);
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

void						Camera::buildLookAtProjection( void )
{
	this->projectionMatrix = glm::perspective(glm::radians(this->fov), this->width / this->height, this->zNear, this->zFar);
	this->modelMatrix = glm::mat4(1.0f);
	this->viewMatrix = glm::lookAt(this->position, this->lookAt, glm::vec3(0,1,0));
	this->modelviewprojectionMatrix = this->projectionMatrix * this->viewMatrix * this->modelMatrix;
}

void						Camera::buildFPSProjection( void )
{
	this->projectionMatrix = glm::perspective(glm::radians(this->fov), this->width / this->height, this->zNear, this->zFar);
	this->modelMatrix = glm::mat4(1.0f);
	this->UpdateView();
	this->modelviewprojectionMatrix = this->projectionMatrix * this->viewMatrix * this->modelMatrix;
}

void						Camera::setProjection(float fov, float width, float height, float zNear, float zFar)
{
	this->fov = fov;
	this->width = width;
	this->height = height;
	this->zNear = zNear;
	this->zFar = zFar;
}

void						Camera::setLookAt(float x, float y, float z)
{
	this->lookAt.x = x;
	this->lookAt.y = y;
	this->lookAt.z = z;
}

void						Camera::setLookAt(glm::vec3 const &v)
{
	this->setLookAt(v.x, v.y, v.z);
}

glm::vec3					&Camera::getLookAt( void )
{
	return (this->lookAt);
}

void						Camera::setPosition(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

void						Camera::setPosition(glm::vec3 const &v)
{
	this->setPosition(v.x, v.y, v.z);
}

glm::vec3					&Camera::getPosition( void )
{
	return (this->position);
}

void						Camera::setDirection(float x, float y, float z)
{
	this->direction.x = x;
	this->direction.y = y;
	this->direction.z = z;
}

void						Camera::setDirection(glm::vec3 const &v)
{
	this->setDirection(v.x, v.y, v.z);
}

glm::vec3					&Camera::getDirection( void )
{
	return (this->direction);
}

void						Camera::setRotation(float x, float y, float z)
{
	this->rotation.x = x;
	this->rotation.y = y;
	this->rotation.z = z;
}

void						Camera::setRotation(glm::vec3 const &v)
{
	this->setRotation(v.x, v.y, v.z);
}

glm::vec3					&Camera::getRotation( void )
{
	return (this->rotation);
}

void					Camera::move(glm::vec3 const &toDirection)
{
	glm::mat4 mat = this->viewMatrix;
	//row major
	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	const float speed = 0.09f;//how fast we move

	this->position += (-toDirection.z * forward + toDirection.x * strafe) * speed;
}

void					Camera::MouseMove(int x, int y)
{
	glm::vec2 mouse_delta = glm::vec2(x, y) - this->mousePosition;

	const float mouseX_Sensitivity = 0.025f;
	const float mouseY_Sensitivity = 0.025f;

	this->rotation.y += mouseX_Sensitivity * mouse_delta.x;
	this->rotation.x += mouseY_Sensitivity * mouse_delta.y;

	this->mousePosition = glm::vec2(x, y);
}

void					Camera::UpdateView()
{
	glm::mat4 matRoll  = glm::mat4(1.0f);//identity matrix;
	glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
	glm::mat4 matYaw   = glm::mat4(1.0f);//identity matrix

	//roll, pitch and yaw are used to store our angles in our class
	matRoll  = glm::rotate(matRoll,  this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	matPitch = glm::rotate(matPitch, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw   = glm::rotate(matYaw,  this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 rotate = matRoll * matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -this->position);

	this->viewMatrix = rotate * translate;
}

// ###############################################################
