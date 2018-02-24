#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Button::Button ( const char *text, const char *style )
{
	this->initialize(NULL);
	return ;
}

Button::Button ( std::string text, const char *style )
{
	this->initialize(NULL);
	return ;
}

Button::Button ( Button const & src )
{
	*this = src;
	return ;
}

Button &					Button::operator=( Button const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Button::~Button ( void )
{
	//KeyBoard::instance->removeHandler("Button");
	return ;
}

std::ostream &				operator<<(std::ostream & o, Button const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

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

void						Button::setFloat(e_float_position position)
{

}

void						Button::setFontFamily(const char *fontname)
{

}

void						Button::setFontSize(int font_size)
{

}

void						Button::setColor(glm::vec3 &color)
{

}

void						Button::setTextAlign(e_float_position position)
{

}

void						Button::setBackgroundColor(glm::vec3 &color)
{

}

void						Button::setBackgroundImage(const char *path)
{

}

void						Button::setDisplay(bool visible)
{

}

void						Button::setStyle(const char *style)
{
	// std::string css_pattern = (std::ostringstream() << css).str();
	// std::vector<std::string> splt = split(css_pattern, ';');
    //
	// for (int command_n = 0; command_n < splt.size(); command_n++)
	// {
	// 	std::string cmd_line = splt.at(command_n);
	// 	std::string cmd = split(cmd_line, ':').at(0);
	// 	std::string value = split(cmd_line, ':').at(1);
    //
	// 	if (cmd == "float") {
	// 		if (value == "left")
	// 			this->text_position = TEXT_LEFT;
	// 		if (value == "right")
	// 			this->text_position = TEXT_RIGHT;
	// 		if (value == "center")
	// 			this->text_position = TEXT_CENTER;
	// 	} else if (cmd == "onfocus") {
	// 		//TODO text add prompt animation
	// 	} else if (cmd == "background-color") {//1,1,1 rgb
	// 		glm::vec3 color;
	// 		colorConverter(color, value);
	// 		this->background->setColor(color.x, color.y, color.z);
	// 	} else if (cmd == "color") {//1,1,1 rgb text color
	// 		glm::vec3 color;
	// 		colorConverter(color, value);
	// 		this->text->setColor(color.x, color.y, color.z);
	// 	} else if (cmd == "font-size") {
	// 		//int size = atoi(value);
	// 	}
	// }
}

void						Button::draw(SDL_Surface *surface)
{
	glm::vec3 parent_position = glm::vec3(0,0,0);

	this->draw(surface, parent_position);
}

void						Button::draw(SDL_Surface *surface, glm::vec3 &parent_position)
{
	this->background->draw(surface, this->transform.position);
	if (this->image != NULL) {
		this->image->draw(surface, this->transform.position);
	}
	this->text->draw(surface, this->transform.position);
}

// ###############################################################

void						Button::initialize(Text *text)
{
	this->text = text;
}
