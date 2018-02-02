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

	for (int i = 0; i < 10; i++) {
		this->components.insert(this->components.begin(), new Cube(1 + (i * 4),1,1,1));
	}

	for (int i = 0; i < 10; i++) {
		this->components.at(i)->produce();
	}

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


	glUseProgram(ShaderUtils::instance->get("simple"));

	BombermanClient::instance->transform->setProjection(45.0f, 16.0f, 9.0f, 0.1f, 100.0f);
	glm::mat4 MVP = BombermanClient::instance->transform->enableProjectionTransformation();

	for (int i = 0; i < 10; i++) {
		this->components.at(i)->render(&MVP[0][0]);
	}
}

void 						SimpleView::pressRight( void )
{
	BombermanClient::instance->camera->getPosition()->x += 1;
	std::cout << "Right" << std::endl;
}

void 						SimpleView::pressLeft( void )
{
	BombermanClient::instance->camera->getPosition()->x -= 1;
	std::cout << "Left" << std::endl;
}

void 						SimpleView::pressUp( void )
{
	BombermanClient::instance->camera->getPosition()->y += 1;
	std::cout << "Up" << std::endl;
}

void 						SimpleView::pressDown( void )
{
	BombermanClient::instance->camera->getPosition()->y -= 1;
	std::cout << "Down" << std::endl;
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
