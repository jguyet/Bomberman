#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

QuitMenuInterface::QuitMenuInterface ( GameScene *scene ) : UIInterface("themes/QuitMenuInterface.html")
{
	this->scene = scene;
	this->current_position = 0;
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->canvas_width, BombermanClient::getInstance()->screen->canvas_height);
	this->canvas->setElementsMap(&this->elements);
	KeyBoard::instance->addHandler("QuitMenuInterface", this);
	return ;
}

QuitMenuInterface::QuitMenuInterface ( QuitMenuInterface const & src ) : UIInterface("unknow")
{
	*this = src;
	return ;
}

QuitMenuInterface &				QuitMenuInterface::operator=( QuitMenuInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

QuitMenuInterface::~QuitMenuInterface ( void )
{
	KeyBoard::instance->removeHandler("QuitMenuInterface");
	delete this->canvas;
	return ;
}

std::ostream &				operator<<(std::ostream & o, QuitMenuInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						QuitMenuInterface::draw(void)
{
	this->variables["$selected"] = (std::ostringstream() << this->current_position).str();
	this->build();
	if (this->modified == true) {
		this->canvas->setElementsMap(&this->elements);
	}
	this->canvas->draw();
}

void						QuitMenuInterface::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_RETURN && this->current_position == 0) {
		BombermanClient::getInstance()->setCurrentScene<GameScene>(new MainMenuScene());
		return ;
	}
	if (key == SDL_SCANCODE_RETURN && this->current_position == 1) {
		this->scene->closeQuitInterface();
	}
	if (key == SDL_SCANCODE_UP) {
		this->current_position = (this->current_position - 1) < 0 ? 1 : (this->current_position - 1) % 2;
	}
	if (key == SDL_SCANCODE_DOWN) {
		this->current_position = (this->current_position + 1) % 2;
	}
}

// ###############################################################
