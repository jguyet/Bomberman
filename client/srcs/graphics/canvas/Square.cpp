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

void						Square::setFloat(e_tag_position position)
{
	this->position = position;
}

void						Square::setFontFamily(std::string const &fontname)
{

}

void						Square::setFontSize(int font_size)
{

}

void						Square::setColor(glm::vec3 &color)
{
	this->color.r = static_cast<Uint8>(color.x);
	this->color.g = static_cast<Uint8>(color.y);
	this->color.b = static_cast<Uint8>(color.z);
}

void						Square::setTextAlign(e_tag_position position)
{

}

void						Square::setBackgroundColor(glm::vec3 &color)
{
	this->setColor(color);
}

void						Square::setBackgroundImage(std::string const &path)
{

}

void						Square::setDisplay(bool visible)
{

}

void						Square::setStyle(std::string const &style)
{
	CSSInterpretor::interpretCSS(this, style);
}

void						Square::draw(SDL_Surface *surface)
{
	SDL_Rect rect;

	glm::vec3	final_position = glm::vec3(0,0,0);
	glm::vec3	final_scale = glm::vec3(0,0,0);

	final_position = this->getPosition(surface);
	final_scale = this->getScale();

	rect.x = final_position.x;
	rect.y = final_position.y;
	rect.w = final_scale.x;
	rect.h = final_scale.y;

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

bool						Square::equals(Tag *tag)
{
	Square *square = dynamic_cast<Square*>(tag);

	if (square->transform.position != this->transform.position)
		return false;
	if (square->transform.scale != this->transform.scale)
		return false;
	if (square->color.r != this->color.r)
		return false;
	if (square->color.g != this->color.g)
		return false;
	if (square->color.b != this->color.b)
		return false;
	return true;
}

// ###############################################################
