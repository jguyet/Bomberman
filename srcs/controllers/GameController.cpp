#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

GameController::GameController ( void )
{
	this->camera = new Camera();
	this->camera->setProjection(45.0f, 1680, 1050, 0.1f, 1000.0f);
	this->camera->transform.position = glm::vec3(11.31f, 31.3938f, -18.231f);
	this->camera->transform.rotation = glm::vec3(57.38f, 98.98f, 0.0f);
	this->camera->buildFPSProjection();

	this->keyBoard_map[87] = &GameController::pressUp;
	this->keyBoard_map[68] = &GameController::pressRight;
	this->keyBoard_map[65] = &GameController::pressLeft;
	this->keyBoard_map[83] = &GameController::pressDown;
	this->keyBoard_map[32] = &GameController::pressSpace;
	this->keyBoard_map[256] = &GameController::Escape;

	//fleche droite 262, bas 264, haut 265, gauche 263

	this->keyBoard_map[262] = &GameController::R;
	this->keyBoard_map[263] = &GameController::L;
	this->keyBoard_map[265] = &GameController::H;
	this->keyBoard_map[264] = &GameController::B;

	this->map = new Map();

	this->p.position = glm::vec3(1 * 10,0,1 * 10);
	this->p.scale = glm::vec3(0.1f,0.1f,0.1f);
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
	this->camera->setProjection(40.0f, 1680, 1050, 0.1f, 1000.0f);
	this->camera->buildLookAtProjection();
	//this->camera->buildFPSProjection();

	this->map->render(this->camera->projectionMatrix, this->camera->viewMatrix);

	glm::vec3 position = glm::vec3(13,0,13);
	glm::vec3 scale = glm::vec3(0.08f,0.08f,0.08f);
	glm::vec3 rotation = glm::vec3(0,0,0);

	Model::model["bomberman"]->draw(position, rotation, scale, this->camera->projectionMatrix, this->camera->viewMatrix);
	std::cout << "x:" << this->camera->transform.position.x << "y:" << this->camera->transform.position.y << "z:" << this->camera->transform.position.z << std::endl;

	Model::model["bomberman2"]->draw(this->p.position, this->p.rotation, this->p.scale, this->camera->projectionMatrix, this->camera->viewMatrix);
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
	this->p.position.z += 0.3f;
}

void						GameController::L(void)
{
	this->p.position.z -= 0.3f;
}

void						GameController::H(void)
{
	this->p.position.x += 0.3f;
}

void						GameController::B(void)
{
	this->p.position.x -= 0.3f;
}

// ###############################################################
