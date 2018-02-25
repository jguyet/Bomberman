#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

MainMenuInterface::MainMenuInterface ( void ) : UIInterface("unknow")
{
	this->current_position = 0;
	this->canvas = new Canvas(BombermanClient::instance->screen->width, BombermanClient::instance->screen->height);

	// Image *img = new Image("assets/ui/mainmenuinterface/background.jpg", 1024, 819, BombermanClient::instance->screen->width, BombermanClient::instance->screen->height);
	// img->transform.position.x = 0;
	// img->transform.position.y = 0;
	// this->canvas->addImage("background", img);
    //
	// Square *square = new Square((BombermanClient::instance->screen->width / 2) - 300, 100, 600, 600);
	// square->setColor(27,36,38);
	// this->canvas->addSquare("bg", square);
    //
	// Square *input = new Square(square->transform.position.x + (square->transform.scale.x / 2) - 150, 400, 300, 40);
	// input->setColor(255,255,255);
	// this->canvas->addSquare("input", input);
    //
	// Text *login_lbl = new Text("Server ip :");
	// login_lbl->transform.position.x = square->transform.position.x + (square->transform.scale.x / 2) - 150;
	// login_lbl->transform.position.y = 350;
	// this->canvas->addText("lbl_input", login_lbl);
    //
	// Text *play = new Text("SELECT SERVER");
	// play->transform.position.x = (BombermanClient::instance->screen->width / 2) - 115;
	// play->transform.position.y = 100;
	// this->canvas->addText("btn_play", play);
    //
	// this->input_lbl = new Text("127.0.0.1");
	// this->input_lbl->setColor(0,0,0);
	// this->input_lbl->transform.position.x = square->transform.position.x + (square->transform.scale.x / 2) - 150;
	// this->input_lbl->transform.position.y = 401;
	// this->canvas->addText("lbl_ip", this->input_lbl);
    //
	// this->button = new Button(new Text("SELECT SERVER"), 150, 150, 100, 100);
	// this->button->css("color:#ff0000;background-color:#ffffff");
	// this->canvas->addButton("Local", this->button);
	return ;
}

MainMenuInterface::MainMenuInterface ( MainMenuInterface const & src ) : UIInterface("")
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
