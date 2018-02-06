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
	this->modeltest = Model::load("assets/grass.obj");

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
	BombermanClient::instance->camera->buildFPSProjection();

	glm::mat4 MVP = BombermanClient::instance->camera->modelviewprojectionMatrix;

	// for (int i = 0; i < 2; i++) {
	// 	this->components.at(i)->render(&MVP[0][0]);
	// }

	glm::vec3 scale = glm::vec3(1,1,1);
	glm::vec3 pos = glm::vec3(1,1,1);
	this->modeltest->draw(pos, scale);
	scale = glm::vec3(1,1,1);
	pos = glm::vec3(2 + 1,1,2 + 1);
	this->modeltest->draw(pos, scale);
	//this->modeltest->render(&MVP[0][0]);
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
