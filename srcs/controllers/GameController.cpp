#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

GameController::GameController ( void )
{
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::instance->screen->width, BombermanClient::instance->screen->height, 0.1f, 1000.0f);
	this->camera->transform.position = glm::vec3(-3.4917f,36.6297f,-17.5657f);
	this->camera->transform.rotation = glm::vec3(78.0803f,269.888f,0);
	this->camera->buildFPSProjection();

	this->keyBoard_map[SDL_SCANCODE_W] = &GameController::pressUp;
	this->keyBoard_map[SDL_SCANCODE_D] = &GameController::pressRight;
	this->keyBoard_map[SDL_SCANCODE_A] = &GameController::pressLeft;
	this->keyBoard_map[SDL_SCANCODE_S] = &GameController::pressDown;
	this->keyBoard_map[SDL_SCANCODE_SPACE] = &GameController::pressSpace;
	this->keyBoard_map[SDL_SCANCODE_ESCAPE] = &GameController::Escape;

	this->keyBoard_map[SDL_SCANCODE_RIGHT] = &GameController::R;
	this->keyBoard_map[SDL_SCANCODE_LEFT] = &GameController::L;
	this->keyBoard_map[SDL_SCANCODE_UP] = &GameController::H;
	this->keyBoard_map[SDL_SCANCODE_DOWN] = &GameController::B;

	this->map = new Map();

	this->p.position = glm::vec3(2,1.f,4);
	this->p.scale = glm::vec3(0.125f,0.125f,0.125f);
	this->p.rotation = glm::vec3(0,0,0);

	this->loaded = true;
	return ;
}

GameController::GameController ( GameController const & src )
{
	*this = src;
	return ;
}

GameController &				GameController::operator=( GameController const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameController::~GameController ( void )
{
	delete this->camera;
	delete this->map;
	return ;
}

std::ostream &				operator<<(std::ostream & o, GameController const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						GameController::process(void)
{
	KeyBoard::instance->process(this);
}

void						GameController::render(void)
{
	if (this->loaded == false)
		return ;
	this->camera->setProjection(40.0f, BombermanClient::instance->screen->width, BombermanClient::instance->screen->height, 0.1f, 1000.0f);
	//this->camera->buildLookAtProjection();
	this->camera->buildFPSProjection();

	this->map->render(this->camera->projectionMatrix, this->camera->viewMatrix);

	Transform transform;
	transform.position = glm::vec3(30,-5,0);
	static float i = 0;
	i = fmod(i + 1, 360);
	transform.rotation = glm::vec3(0,i,0);
	transform.scale = glm::vec3(1,1,1);
	Model::model["N64"]->draw(transform.position, transform.rotation, transform.scale, this->camera->projectionMatrix, this->camera->viewMatrix);

	static float o = 2.5f;
	static bool up = false;
	if (up == true)
		o += 0.03f;
	if (up == false)
		o -= 0.03f;
	if (o < 1)
		up = true;
	if (o > 2.5f)
		up = false;
	transform.position = glm::vec3(2,0,2);
	transform.rotation = glm::vec3(0,0,0);
	transform.scale = glm::vec3(o,o,o);

	Model::model["bomb"]->draw(transform.position, transform.rotation, transform.scale, this->camera->projectionMatrix, this->camera->viewMatrix);

	//std::cout << "x:" << this->camera->transform.position.x << "y:" << this->camera->transform.position.y << "z:" << this->camera->transform.position.z << std::endl;

	Model::model["bomberman"]->draw(this->p.position, this->p.rotation, this->p.scale, this->camera->projectionMatrix, this->camera->viewMatrix);
}

// ###############################################################

// INPUTS METHOD #################################################

void						GameController::pressKeyBoard(unsigned int key)
{
	if (this->keyBoard_map.count(key) == 1) {
		(this->*keyBoard_map[key])();
	}
}

void						GameController::pressMouseButton(unsigned int button)
{

}

void 						GameController::Escape( void )
{
	BombermanClient::instance->stop();
}

void 						GameController::pressRight( void )
{
	this->camera->move(glm::vec3(2, 0, 0));
}

void 						GameController::pressLeft( void )
{
	this->camera->move(glm::vec3(-2, 0, 0));
}

void 						GameController::pressUp( void )
{
	this->camera->move(glm::vec3(0, 0, 2));
}

void 						GameController::pressDown( void )
{
	this->camera->move(glm::vec3(0, 0, -2));
}

void 						GameController::pressSpace( void )
{
	this->camera->transform.position.y += 0.5f;
}


void						GameController::R(void)
{
	if (this->p.rotation.y != 180.f) {
		this->p.rotation.y = 180.f;
	}
	this->p.position.z += 0.1f;
}

void						GameController::L(void)
{
	if (this->p.rotation.y != 0.f) {
		this->p.rotation.y = 0.f;
	}
	this->p.position.z -= 0.1f;
}

void						GameController::H(void)
{
	if (this->p.rotation.y != 270.f) {
		this->p.rotation.y = 270.f;
	}
	this->p.position.x += 0.1f;
}

void						GameController::B(void)
{
	if (this->p.rotation.y != 90.f) {
		this->p.rotation.y = 90.f;
	}
	this->p.position.x -= 0.1f;
}

// ###############################################################
