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

void						Square::setFontFamily(const char *fontname)
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

void						Square::setBackgroundImage(const char *path)
{

}

void						Square::setDisplay(bool visible)
{

}

void						Square::setStyle(const char *style)
{
	CSSInterpretor::interpretCSS(this, style);
}

void						Square::draw(SDL_Surface *surface)
{
	glm::vec3 parent_position = glm::vec3(0,0,0);
	glm::vec3 parent_scale = glm::vec3(0,0,0);

	parent_scale.x = surface->w;
	parent_scale.y = surface->h;

	if (this->parent != NULL) {
		parent_position.x = this->parent->transform.position.x;
		parent_position.y = this->parent->transform.position.y;
		parent_scale.x = this->parent->transform.scale.x;
		parent_scale.y = this->parent->transform.scale.y;
	}
	this->draw(surface, parent_position, parent_scale);
}

void						Square::draw(SDL_Surface *surface, glm::vec3 &parent_position, glm::vec3 &parent_scale)
{
	SDL_Rect rect;

	glm::vec3	final_position = glm::vec3(0,0,0);

	if (this->position == TAG_POSITION_CENTER) {
		this->transform.position.x += parent_position.x + (parent_scale.x / 2);
		this->position = TAG_POSITION_NULL;
	} else if (this->position == TAG_POSITION_LEFT) {
		this->transform.position.x += parent_position.x;
		this->position = TAG_POSITION_NULL;
	} else if (this->position == TAG_POSITION_RIGHT) {
		this->transform.position.x += parent_position.x + parent_scale.x;
		this->position = TAG_POSITION_NULL;
	} else {
		final_position.x = parent_position.x;
		final_position.y = parent_position.y;
	}

	rect.x = this->transform.position.x + final_position.x;
	rect.y = this->transform.position.y + final_position.y;
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
