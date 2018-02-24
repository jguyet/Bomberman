#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

Text::Text (const char *text)
{
	this->initialize(text, "");
	return ;
}

Text::Text (std::string text)
{
	this->saveptr = text;
	this->initialize(this->saveptr.c_str(), "");
	return ;
}

Text::Text (int number)
{
	this->saveptr = (std::ostringstream() << number).str();
	this->initialize(this->saveptr.c_str(), "");
	return ;
}

// Text::Text (const char *text, const char *style) : GameObject()
// {
// 	this->initialize(text, style);
// 	return ;
// }
//
// Text::Text (std::string text, const char *style) : GameObject()
// {
// 	this->saveptr = text;
// 	this->initialize(this->saveptr.c_str(), style);
// 	return ;
// }
//
// Text::Text (int number, const char *style) : GameObject()
// {
// 	this->saveptr = (std::ostringstream() << number).str();
// 	this->initialize(this->saveptr.c_str(), style);
// 	return ;
// }

Text::Text ( Text const & src )
{
	*this = src;
	return ;
}

Text &				Text::operator=( Text const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Text::~Text ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Text const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Text::setFloat(e_float_position position)
{

}

void						Text::setFontFamily(const char *fontname)
{

}

void						Text::setFontSize(int font_size)
{

}

void						Text::setColor(glm::vec3 &color)
{

}

void						Text::setTextAlign(e_float_position position)
{

}

void						Text::setBackgroundColor(glm::vec3 &color)
{

}

void						Text::setBackgroundImage(const char *path)
{

}

void						Text::setDisplay(bool visible)
{

}

void						Text::setStyle(const char *style)
{

}

void						Text::draw(SDL_Surface *surface)
{
	glm::vec3 parent = glm::vec3(0,0,0);

	this->draw(surface, parent);
}

void						Text::draw(SDL_Surface *surface, glm::vec3 &parent_position)
{
	SDL_Rect	text_position;
	SDL_Surface	*text_surface;

	text_position.x = this->transform.position.x + parent_position.x;
	text_position.y = this->transform.position.y + parent_position.y;

	text_surface = TTF_RenderText_Solid(this->font, this->text, this->color);
	SDL_BlitSurface(text_surface, NULL, surface, &text_position);
	SDL_FreeSurface(text_surface);
}

// PRIVATE METHOD ################################################

void						Text::initialize(const char *text, const char *style)
{
	this->text = text;
	this->color = {255, 255, 255,0};
	this->font = NULL;
	//this->setFont("arial", 30);
	//this->css(style);
}

// ###############################################################
