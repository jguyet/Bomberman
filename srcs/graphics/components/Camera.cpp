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

void					Camera::MouseMove(glm::vec2 &lastMousePosition, glm::vec2 &mousePosition)
{
	glm::vec2 mouse_delta = mousePosition - lastMousePosition;

	const float mouseX_Sensitivity = 0.0025f;
	const float mouseY_Sensitivity = 0.0025f;

	if (mouse_delta.x != 0) {
		this->transform.rotation.y += (360/(M_PI * 2)) * (mouseX_Sensitivity * mouse_delta.x);
		this->transform.rotation.y = fmod(this->transform.rotation.y, 360.f);
		if (this->transform.rotation.y < 0)
			this->transform.rotation.y = 360 + this->transform.rotation.y;
	}
	if (mouse_delta.y != 0) {
		this->transform.rotation.x += (360/(M_PI * 2)) * (mouseY_Sensitivity * mouse_delta.y);
		this->transform.rotation.x = fmod(this->transform.rotation.x, 360.f);
		if (this->transform.rotation.x < 0)
			this->transform.rotation.x = 360 + this->transform.rotation.x;
	}
}

void					Camera::UpdateView()
{
	glm::mat4 matRoll  = glm::mat4(1.0f);//identity matrix;
	glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
	glm::mat4 matYaw   = glm::mat4(1.0f);//identity matrix

	//roll, pitch and yaw are used to store our angles in our class
	float x = this->transform.rotation.x;
	float y = this->transform.rotation.y;
	float z = this->transform.rotation.z;
	x = x * (M_PI * 2) / 360;
	y = y * (M_PI * 2) / 360;
	z = z * (M_PI * 2) / 360;
	matPitch = glm::rotate(matPitch, x, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw   = glm::rotate(matYaw,  y, glm::vec3(0.0f, 1.0f, 0.0f));
	matRoll  = glm::rotate(matRoll, z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 rotate = matRoll * matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -this->transform.position);

	this->viewMatrix = rotate * translate;
}

// ###############################################################
