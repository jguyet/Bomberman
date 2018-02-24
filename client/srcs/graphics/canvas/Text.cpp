#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

Text::Text (const char *text) : GameObject()
{
	this->initialize(text, "");
	return ;
}

Text::Text (std::string text) : GameObject()
{
	this->saveptr = text;
	this->initialize(this->saveptr.c_str(), "");
	return ;
}

Text::Text (int number) : GameObject()
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

void								Text::setColor(int r, int g, int b)
{
	this->color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b),0};
}

void								Text::setFont(const char *font, int size)
{
	if (this->font != NULL) {
		TTF_CloseFont(this->font);
	}
	std::string sfont = (std::ostringstream() << "assets/fonts/" << font << ".ttf").str();
	this->font = TTF_OpenFont(sfont.c_str(), size);
}

void								Text::setFont(std::string font, int size)
{
	this->setFont(font.c_str(), size);
}

void								Text::setText(const char *text)
{
	this->text = text;
}

void								Text::setText(std::string text)
{
	this->saveptr = text;
	this->text = this->saveptr.c_str();
}

void						Text::draw(SDL_Surface *surface)
{
	glm::vec3 parent;

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

void						Text::css(const char *style)
{

}

// PRIVATE METHOD ################################################

void						Text::initialize(const char *text, const char *style)
{
	this->text = text;
	this->color = {255, 255, 255,0};
	this->font = NULL;
	this->setFont("arial", 30);
	this->css(style);
}

// ###############################################################
