#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Button::Button ( Text *text, int x, int y, int width, int height )
{
	this->initialize(NULL, text, TEXT_CENTER, x, y, width, height);
	return ;
}

Button::Button ( Text *text, e_text_position position, int x, int y, int width, int height )
{
	this->initialize(NULL, text, position, x, y, width, height);
	return ;
}

Button::Button ( Button const & src )
{
	*this = src;
	return ;
}

Button &				Button::operator=( Button const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Button::~Button ( void )
{
	KeyBoard::instance->removeHandler("Button");
	return ;
}

std::ostream &				operator<<(std::ostream & o, Button const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Button::draw(SDL_Surface *surface)
{
	this->background->draw(surface, this->transform.position);
	if (this->image != NULL) {
		this->image->draw(surface, this->transform.position);
	}
	this->text->draw(surface, this->transform.position);
}

void						Button::addTexture(Image *image)
{
	this->image = image;
}

void						colorConverter(glm::vec3 &color, std::string hexcolor)
{
	int r, g, b;

	if (hexcolor.substr(0, 1) == "#")
		hexcolor.erase(0,1);
	sscanf(hexcolor.c_str(), "%02x%02x%02x", &r, &g, &b);
	color.x = r;
	color.y = g;
	color.z = b;
}

void						Button::css(const char *css)
{
	std::string css_pattern = (std::ostringstream() << css).str();
	std::vector<std::string> splt = split(css_pattern, ';');

	for (int command_n = 0; command_n < splt.size(); command_n++)
	{
		std::string cmd_line = splt.at(command_n);
		std::string cmd = split(cmd_line, ':').at(0);
		std::string value = split(cmd_line, ':').at(1);

		if (cmd == "float") {
			if (value == "left")
				this->text_position = TEXT_LEFT;
			if (value == "right")
				this->text_position = TEXT_RIGHT;
			if (value == "center")
				this->text_position = TEXT_CENTER;
		} else if (cmd == "onfocus") {
			//TODO text add prompt animation
		} else if (cmd == "background-color") {//1,1,1 rgb
			glm::vec3 color;
			colorConverter(color, value);
			this->background->setColor(color.x, color.y, color.z);
		} else if (cmd == "color") {//1,1,1 rgb text color
			glm::vec3 color;
			colorConverter(color, value);
			this->text->setColor(color.x, color.y, color.z);
		} else if (cmd == "font-size") {
			int size = atoi(value);

		}
	}

}

void						Button::handleUP(unsigned int key)
{
	//std::cout << "Up      Key(" << key << ")" << std::endl;
}

void						Button::handleDOWN(unsigned int key)
{
	//std::cout << "Down    Key(" << key << ")" << std::endl;
}

void						Button::handleRELEASE(unsigned int key)
{
	//std::cout << "Release Key(" << key << ")" << std::endl;
}

// ###############################################################

void						Button::initialize(Image *image, Text *text, e_text_position position, int x, int y, int width, int height)
{
	this->image = image;
	this->text = text;
	this->text_position = position;
	this->background = new Square(0, 0, width, height);
	this->background->setColor(0,0,0);
	KeyBoard::instance->addHandler("Button", this);
}
