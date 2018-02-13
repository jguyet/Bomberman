#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

GameInterface::GameInterface ( int number_of_player )
{
	this->number_of_player = number_of_player;
	this->canvas = new Canvas(BombermanClient::instance->screen->width, BombermanClient::instance->screen->height);

	for (int i = 0; i < 5; i++) {
		Image *img = new Image("assets/head_bomberman/blue_head.png");
		img->transform.position.x = (i * 100) + 10;
		Text *t1 = new Text("0");
		t1->transform.position.x = (i * 100) + 63;
		t1->transform.position.y = 8;

		std::ostringstream ss = std::ostringstream();
		ss << "text_player_";
		ss << i;
		std::string text_p(ss.str());
		this->canvas->addText(text_p.c_str(), t1);

		ss = std::ostringstream();
		ss << "img_player_";
		ss << i;
		std::string img_p(ss.str());

		this->canvas->addImage(img_p.c_str(), img);
	}

	// for (int i = 0; i < 5; i++) {
	// 	Image img = Image("assets/head_bomberman/green_head.png");
	// 	img.transform.position.x = (i * 100) + (BombermanClient::instance->screen->width - 510);
	// 	Text t1 = Text("0");
	// 	t1.transform.position.x = (i * 100) + (BombermanClient::instance->screen->width- 510) + 53;
	// 	t1.transform.position.y = 8;
	// 	this->canvas->addText(t1);
	// 	this->canvas->addImage(img);
	// }
	Image *img = new Image("assets/clock_over.png");
	img->transform.position.x = (BombermanClient::instance->screen->width / 2) - 70;
	img->transform.position.y = 5;
	this->canvas->addImage("clock_ground", img);

	Text *timer = new Text("1 : 43");
	timer->transform.position.x = (BombermanClient::instance->screen->width / 2) - 50;
	timer->transform.position.y = 8;
	this->canvas->addText("clock", timer);

	return ;
}

GameInterface::GameInterface ( GameInterface const & src )
{
	*this = src;
	return ;
}

GameInterface &				GameInterface::operator=( GameInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameInterface::~GameInterface ( void )
{
	delete this->canvas;
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, GameInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						GameInterface::draw(void)
{
	this->canvas->draw();
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
