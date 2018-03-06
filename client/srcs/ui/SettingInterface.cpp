#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

SettingInterface::SettingInterface ( void ) : UIInterface("themes/SettingInterface.html")
{
	this->current_position = 0;
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->canvas_width, BombermanClient::getInstance()->screen->canvas_height);
	this->canvas->setElementsMap(&this->elements);
	KeyBoard::instance->addHandler("SettingInterface", this);
	return ;
}

SettingInterface::SettingInterface ( SettingInterface const & src ) : UIInterface("unknow")
{
	*this = src;
	return ;
}

SettingInterface &				SettingInterface::operator=( SettingInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

SettingInterface::~SettingInterface ( void )
{
	KeyBoard::instance->removeHandler("SettingInterface");
	return ;
}

std::ostream &				operator<<(std::ostream & o, SettingInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void								SettingInterface::draw(void)
{
	int width = BombermanClient::getInstance()->screen->width;
	int height = BombermanClient::getInstance()->screen->height;
	bool fullscreen = BombermanClient::getInstance()->screen->fullscreen;

	if (KeyBoard::instance->getKey(SDL_SCANCODE_RIGHT) && this->current_position == 0 && width < 2000 && fullscreen == false) {
		width += 10;
		BombermanClient::getInstance()->setWindowSize(width, height, fullscreen);
	}

	if (KeyBoard::instance->getKey(SDL_SCANCODE_LEFT) && this->current_position == 0 && width > 0 && fullscreen == false) {
		width -= 10;
		BombermanClient::getInstance()->setWindowSize(width, height, fullscreen);
	}

	if (KeyBoard::instance->getKey(SDL_SCANCODE_RIGHT) && this->current_position == 1 && height < 2000 && fullscreen == false) {
		height += 10;
		BombermanClient::getInstance()->setWindowSize(width, height, fullscreen);
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_LEFT) && this->current_position == 1 && height > 0 && fullscreen == false) {
		height -= 10;
		BombermanClient::getInstance()->setWindowSize(width, height, fullscreen);
	}

	//FULLSCREEN
	if (KeyBoard::instance->getKey(SDL_SCANCODE_LEFT) && this->current_position == 2 && fullscreen == false) {
		BombermanClient::getInstance()->setWindowSize(width, height, true);
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_RIGHT) && this->current_position == 2 && fullscreen == true) {
		BombermanClient::getInstance()->setWindowSize(width, height, false);
	}
	//SOUND
	if (KeyBoard::instance->getKey(SDL_SCANCODE_LEFT) && this->current_position == 3) {
		BombermanClient::getInstance()->enableSound = true;
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_RIGHT) && this->current_position == 3) {
		BombermanClient::getInstance()->enableSound = false;
	}

	//Music
	if (KeyBoard::instance->getKey(SDL_SCANCODE_LEFT) && this->current_position == 4) {
		BombermanClient::getInstance()->enableMusic = true;
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_RIGHT) && this->current_position == 4) {
		BombermanClient::getInstance()->enableMusic = false;
	}

	this->variables["$sound"] = BombermanClient::getInstance()->enableSound ? "true" : "false";
	this->variables["$music"] = BombermanClient::getInstance()->enableMusic ? "true" : "false";
	this->variables["$fullscreen"] = fullscreen ? "true" : "false";
	this->variables["$width"] = (std::ostringstream() << width).str();
	this->variables["$w_size"] = (std::ostringstream() << (width * 300 / 2000)).str();
	this->variables["$height"] = (std::ostringstream() << height).str();
	this->variables["$h_size"] = (std::ostringstream() << (height * 300 / 2000)).str();
	this->variables["$selected"] = (std::ostringstream() << this->current_position).str();

	this->build();
	if (this->modified == true) {
		this->canvas->setElementsMap(&this->elements);
	}
	this->canvas->draw();
}

void								SettingInterface::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_UP) {
		this->current_position = (this->current_position - 1) < 0 ? 4 : (this->current_position - 1) % 6;
	}
	if (key == SDL_SCANCODE_DOWN) {
		this->current_position = (this->current_position + 1) % 6;
	}
}

// ###############################################################
