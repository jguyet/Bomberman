#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Tag::Tag ( void )
{
	this->position = TAG_POSITION_NULL;
	this->parent = NULL;
	this->parent_name = "";
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

glm::vec3 const						Tag::getPosition(SDL_Surface *surface)
{
	glm::vec3		tmp = glm::vec3(0,0,0);

	if (this->parent != NULL && this->parent->id != this->id) {
		glm::vec3 parent_p = this->parent->getPosition(surface);
		glm::vec3 parent_s = this->parent->getScale();

		if (this->position == TAG_POSITION_CENTER) {
			tmp.x = parent_position.x + (parent_s.x / 2);
		} else if (this->position == TAG_POSITION_LEFT) {
			tmp.x = parent_position.x;
		} else if (this->position == TAG_POSITION_RIGHT) {
			tmp.x = parent_p.x + parent_s.x;
		} else {
			tmp.x = parent_p.x;
		}
		tmp.y = parent_p.y;
		tmp.z = parent_p.z;
	} else if (surface != NULL && this->position != TAG_POSITION_NULL) {
		if (this->position == TAG_POSITION_CENTER) {
			tmp.x = 0 + (surface->w / 2);
		} else if (this->position == TAG_POSITION_RIGHT) {
			tmp.x = 0 + surface->w;
		}
	}
	tmp.x += this->transform.position.x;
	tmp.y += this->transform.position.y;
	tmp.z += this->transform.position.z;
	return (tmp);
}

glm::vec3 const						Tag::getScale(void)
{
	glm::vec3		tmp = glm::vec3(0,0,0);

	// if (this->parent != NULL && this->parent->id != this->id) {
	// 	glm::vec3 parent_s = this->parent->getScale();
    //
	// 	tmp.x = parent_s.x;
	// 	tmp.y = parent_s.y;
	// 	tmp.z = parent_s.z;
	// }
	tmp.x += this->transform.scale.x;
	tmp.y += this->transform.scale.y;
	tmp.z += this->transform.scale.z;
	return (tmp);
}

void						Tag::setFloat(e_tag_position position)
{

}

void						Tag::setParent_name(std::string const &parent_name)
{
	this->parent_name = parent_name;
}

void						Tag::setParent(Tag *parent)
{
	this->parent = parent;
}

void						Tag::setFontFamily(std::string const &fontname)
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

void						Tag::setBackgroundImage(std::string const &path)
{

}

void						Tag::setDisplay(bool visible)
{

}

void						Tag::setValue(std::string const &value)
{

}

void						Tag::setStyle(std::string const &style)
{

}

void						Tag::draw(SDL_Surface *surface)
{

}

bool						Tag::equals(Tag *tag)
{
	return false;
}

// ###############################################################
