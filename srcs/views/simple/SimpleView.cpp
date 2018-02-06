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
	this->keyBoard_map[32] = &SimpleView::pressSpace;
	this->keyBoard_map[256] = &SimpleView::Escape;

	// for (int z = 0; z < 2; z++) {
	// 	for (int x = 0; x < 2; x++) {
	// 		this->components.insert(this->components.begin(), new Cube(1 + x,1,1 + z, 1.f));
	// 	}
	// }
    //
	// for (int i = 0; i < 2; i++) {
	// 	this->components.at(i)->produce();
	// }
	this->models[0] = Model::load("assets/ground.obj");
	this->models[1] = Model::load("assets/brick.obj");
	this->models[2] = Model::load("assets/grass.obj");

	//this->modeltest->produce();
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
	BombermanClient::instance->camera->setProjection(45.0f, 1680, 1050, 0.1f, 1000.0f);
	//BombermanClient::instance->camera->buildLookAtProjection();
	BombermanClient::instance->camera->buildFPSProjection();

	glm::mat4 MVP = BombermanClient::instance->camera->modelviewprojectionMatrix;

	// for (int i = 0; i < 2; i++) {
	// 	this->components.at(i)->render(&MVP[0][0]);
	// }

	for (int z = 0; z < 19; z++) {
		for (int x = 0; x < 13;) {
			glm::vec3 scale = glm::vec3(1,1,1);
			glm::vec3 pos = glm::vec3(x,-0.5f,z);
			this->models[1]->draw(pos, scale);
			if (z == 0 || z == 18 || x == 12)
				x++;
			else
				x = 12;
		}
	}



	glm::vec3 scale = glm::vec3(1,1,1);
	glm::vec3 pos = glm::vec3(0,0,0);
	this->models[0]->draw(pos, scale);


	pos = glm::vec3(1,-0.5f,1);
	this->models[1]->draw(pos, scale);

	pos = glm::vec3(4,-0.5f,1);
	this->models[2]->draw(pos, scale);

	//std::cout << "x:" << BombermanClient::instance->camera->getPosition().x << "y:" << BombermanClient::instance->camera->getPosition().y << "z:" << BombermanClient::instance->camera->getPosition().z << std::endl;
}

void 						SimpleView::Escape( void )
{
	BombermanClient::instance->stop();
}

void 						SimpleView::pressRight( void )
{
	BombermanClient::instance->camera->move(glm::vec3(2, 0, 0));
}

void 						SimpleView::pressLeft( void )
{
	BombermanClient::instance->camera->move(glm::vec3(-2, 0, 0));
}

void 						SimpleView::pressUp( void )
{
	BombermanClient::instance->camera->move(glm::vec3(0, 0, 2));
}

void 						SimpleView::pressDown( void )
{
	BombermanClient::instance->camera->move(glm::vec3(0, 0, -2));
}

void 						SimpleView::pressSpace( void )
{
	BombermanClient::instance->camera->getPosition().y += 0.5f;
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
