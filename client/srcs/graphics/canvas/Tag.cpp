#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Tag::Tag ( void )
{
	return ;
}

Tag::Tag ( Tag const & src )
{
	*this = src;
	return ;
}

Tag &				Tag::operator=( Tag const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Tag::~Tag ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Tag const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Tag::setPosition(glm::vec3 &pos)
{
	this->transform.position.x = pos.x;
	this->transform.position.y = pos.y;
}

void						Tag::setWidth(int width)
{
	this->transform.scale.x = width;
};

void						Tag::setHeight(int height)
{
	this->transform.scale.y = height;
};

void						Tag::setFloat(e_tag_position position)
{

}

void						Tag::setFontFamily(const char *fontname)
{

}

void						Tag::setFontSize(int font_size)
{

}

void						Tag::setColor(glm::vec3 &color)
{

}

void						Tag::setTextAlign(e_tag_position position)
{

}

void						Tag::setBackgroundColor(glm::vec3 &color)
{

}

void						Tag::setBackgroundImage(const char *path)
{

}

void						Tag::setDisplay(bool visible)
{

}

void						Tag::setStyle(const char *style)
{

}

void						Tag::draw(SDL_Surface *surface)
{

}

void						Tag::draw(SDL_Surface *surface, glm::vec3 &parent_position)
{

}

// ###############################################################
