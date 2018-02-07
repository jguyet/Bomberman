#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Camera::Camera ( void )
{
	this->UpdateView();
	return ;
}

Camera::Camera (glm::vec3 &position, glm::vec3 &rotation)
{
	this->transform.position = position;
	this->transform.rotation = rotation;
	this->mousePosition = glm::vec3(-1, -1, -1);
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
	this->viewMatrix = glm::lookAt(this->transform.position, glm::vec3(-6.f,1,-9.f), glm::vec3(0,1,0));
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

void					Camera::move(glm::vec3 const &toDirection)
{
	glm::mat4 mat = this->viewMatrix;
	//row major
	glm::vec3 forward = glm::vec3(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 strafe = glm::vec3(mat[0][0], mat[1][0], mat[2][0]);

	const float speed = 0.09f;//how fast we move

	this->transform.position += (-toDirection.z * forward + toDirection.x * strafe) * speed;
}

void					Camera::MouseMove(int x, int y)
{
	if (this->mousePosition.x == -1 && this->mousePosition.y == -1) {
		this->mousePosition = glm::vec2(x, y);
		return ;
	}
	glm::vec2 mouse_delta = glm::vec2(x, y) - this->mousePosition;

	const float mouseX_Sensitivity = 0.0025f;
	const float mouseY_Sensitivity = 0.0025f;

	this->transform.rotation.y += mouseX_Sensitivity * mouse_delta.x;
	this->transform.rotation.x += mouseY_Sensitivity * mouse_delta.y;

	if (this->transform.rotation.x > 58.6f) {
	 	this->transform.rotation.x = 58.6f;
	} else if (this->transform.rotation.x < 55) {
		this->transform.rotation.x = 55;
	}

	this->mousePosition = glm::vec2(x, y);
	//std::cout << "x:" << this->transform.rotation.x << "y:" << this->transform.rotation.y << "z:" << this->transform.rotation.z << std::endl;
}

void					Camera::UpdateView()
{
	glm::mat4 matRoll  = glm::mat4(1.0f);//identity matrix;
	glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
	glm::mat4 matYaw   = glm::mat4(1.0f);//identity matrix

	//roll, pitch and yaw are used to store our angles in our class
	matRoll  = glm::rotate(matRoll,  this->transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	matPitch = glm::rotate(matPitch, this->transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw   = glm::rotate(matYaw,  this->transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 rotate = matRoll * matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -this->transform.position);

	this->viewMatrix = rotate * translate;
}

// ###############################################################
