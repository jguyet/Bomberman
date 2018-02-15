#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

MainMenuInterface::MainMenuInterface ( void )
{
	this->current_position = 0;
	this->canvas = new Canvas(BombermanClient::instance->screen->width, BombermanClient::instance->screen->height);

	Image *img = new Image("assets/ui/mainmenuinterface/background.jpg", 1024, 819, BombermanClient::instance->screen->width, BombermanClient::instance->screen->height);
	img->transform.position.x = 0;
	img->transform.position.y = 0;
	this->canvas->addImage("background", img);
	return ;
}

MainMenuInterface::MainMenuInterface ( MainMenuInterface const & src )
{
	*this = src;
	return ;
}

MainMenuInterface &				MainMenuInterface::operator=( MainMenuInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

MainMenuInterface::~MainMenuInterface ( void )
{
	delete this->canvas;
	return ;
}

std::ostream &				operator<<(std::ostream & o, MainMenuInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						MainMenuInterface::draw(void)
{
	this->canvas->draw();
}

// ###############################################################
