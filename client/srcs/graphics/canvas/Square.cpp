#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Square::Square ( int x, int y, int width, int height )
{
	this->initialize(x, y, width, height);
	return ;
}

Square::Square ( Square const & src )
{
	*this = src;
	return ;
}

Square &				Square::operator=( Square const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Square::~Square ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Square const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Square::setFloat(e_float_position position)
{

}

void						Square::setFontFamily(const char *fontname)
{

}

void						Square::setFontSize(int font_size)
{

}

void						Square::setColor(glm::vec3 &color)
{

}

void						Square::setTextAlign(e_float_position position)
{

}

void						Square::setBackgroundColor(glm::vec3 &color)
{

}

void						Square::setBackgroundImage(const char *path)
{

}

void						Square::setDisplay(bool visible)
{

}

void						Square::setStyle(const char *style)
{

}

void						Square::draw(SDL_Surface *surface)
{
	glm::vec3 parent_position = glm::vec3(0,0,0);

	this->draw(surface, parent_position);
}

void						Square::draw(SDL_Surface *surface, glm::vec3 &parent_position)
{
	SDL_Rect rect;

	rect.x = this->transform.position.x + parent_position.x;
	rect.y = this->transform.position.y + parent_position.y;
	rect.w = this->transform.scale.x;
	rect.h = this->transform.scale.y;

	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, this->color.r, this->color.g, this->color.b));
}

void						Square::initialize( int x, int y, int width, int height )
{
	this->color = {255,255,255,0};
	this->transform.position.x = x;
	this->transform.position.y = y;
	this->transform.scale.x = width;
	this->transform.scale.y = height;
}

// ###############################################################
