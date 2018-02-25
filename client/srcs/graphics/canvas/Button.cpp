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

void						Button::setFloat(e_tag_position position)
{

}

void						Button::setFontFamily(const char *fontname)
{
	this->text->setFontFamily(fontname);
}

void						Button::setFontSize(int font_size)
{

}

void						Button::setColor(glm::vec3 &color)
{
	this->text->setColor(color);
}

void						Button::setTextAlign(e_tag_position position)
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
	CSSInterpretor::interpretCSS(this, style);
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
	this->text->draw(surface, this->transform.position, this->transform.scale);
}

// ###############################################################

void						Button::initialize(Text *text)
{
	this->text = text;
}
