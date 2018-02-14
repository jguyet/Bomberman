#include "Bomberman.hpp"

// CANONICAL #####################################################

GameScene::GameScene ( void )
{
	//CAMERA
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::instance->screen->width, BombermanClient::instance->screen->height, 0.1f, 1000.0f);
	this->camera->transform.position = glm::vec3(-3.4917f,36.6297f,-17.5657f);
	this->camera->transform.rotation = glm::vec3(78.0803f,269.888f,0);
	this->camera->buildFPSProjection();

	//build map
	this->map = new Map(this);

	//add player
	this->player = Factory::newPlayer();
	this->player->transform.position = glm::vec3(2,1,4);
	this->player->transform.scale = glm::vec3(0.125f,0.125f,0.125f);
	this->player->transform.rotation = glm::vec3(0,0,0);
	this->add(this->player);//add on scene

	//add LOGO WESH
	GameObject *logo_N = new GameObject();
	logo_N->AddComponent<Model>(Model::model["N64"]);
	logo_N->transform.position = glm::vec3(30,-5,0);
	logo_N->transform.scale = glm::vec3(1,1,1);
	logo_N->transform.rotation = glm::vec3(0,0,0);
	this->add(logo_N);//add on scene

	this->interface = new GameInterface(1);
	return ;
}

GameScene &				GameScene::operator=( GameScene const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameScene::~GameScene ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, GameScene const & i)
{
	(void)i;
	return (o);
}

// ###############################################################


void								GameScene::calculPhisics(void)
{
	if (KeyBoard::instance->getKey(SDL_SCANCODE_ESCAPE)) {//ESC
		BombermanClient::instance->stop();
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_W)) {//UP
		this->camera->move(glm::vec3(0, 0, 2));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_D)) {//RIGHT
		this->camera->move(glm::vec3(2, 0, 0));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_A)) {//LEFT
		this->camera->move(glm::vec3(-2, 0, 0));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_S)) {//DOWN
		this->camera->move(glm::vec3(0, 0, -2));
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_SPACE)) {//DOWN
		this->camera->transform.position.y += 0.5f;
	}
	//call parent method
	this->_calculPhisics();
}

void								GameScene::drawGameObjects(void)
{
	//build Matrixs
	this->camera->buildFPSProjection();
	//this->camera->buildLookAtProjection(glm::vec3(-12.f,1,-18.f));
	//call parent method
	this->_drawGameObjects();
	//draw canvas
	this->interface->draw();
}
