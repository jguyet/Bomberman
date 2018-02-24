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

void								Square::setColor(int r, int g, int b)
{
	this->color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b),0};
}

void								Square::draw(SDL_Surface *surface)
{
	SDL_Rect rect;

	rect.x = this->transform.position.x;
	rect.y = this->transform.position.y;
	rect.w = this->transform.scale.x;
	rect.h = this->transform.scale.y;

	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, this->color.r, this->color.g, this->color.b));
}

void								Square::draw(SDL_Surface *surface, glm::vec3 &parent_position)
{
	SDL_Rect rect;

	rect.x = this->transform.position.x + parent_position.x;
	rect.y = this->transform.position.y + parent_position.y;
	rect.w = this->transform.scale.x;
	rect.h = this->transform.scale.y;

	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, this->color.r, this->color.g, this->color.b));
}

void								Square::initialize( int x, int y, int width, int height )
{
	this->color = {255,255,255,0};
	this->transform.position.x = x;
	this->transform.position.y = y;
	this->transform.scale.x = width;
	this->transform.scale.y = height;
}

// ###############################################################
