#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

Text::Text (const char *text, const char *style)
{
	this->initialize(text, style);
	return ;
}

Text::Text (std::string text, const char *style)
{
	this->saveptr = text;
	this->initialize(this->saveptr.c_str(), style);
	return ;
}

Text::Text (int number, const char *style)
{
	this->saveptr = (std::ostringstream() << number).str();
	this->initialize(this->saveptr.c_str(), style);
	return ;
}

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

void						Text::setFloat(e_tag_position position)
{
	this->position = position;
}

void						Text::setFontFamily(const char *fontname)
{
	std::ostringstream s;
	std::ostringstream sfontName;

	sfontName << fontname;

	this->fontName = sfontName.str();
	s << "assets/fonts/" << this->fontName << ".ttf";
	std::string font_path = s.str();
	this->font = TTF_OpenFont(font_path.c_str(), this->fontSize);
}

void						Text::setFontSize(int font_size)
{
	this->fontSize = font_size;
	if (this->font != NULL)
		this->setFontFamily(this->fontName.c_str());
}

void						Text::setColor(glm::vec3 &color)
{
	this->color = {static_cast<Uint8>(color.x), static_cast<Uint8>(color.y), static_cast<Uint8>(color.z)};
}

void						Text::setTextAlign(e_tag_position position)
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
	CSSInterpretor::interpretCSS(this, style);
}

void						Text::draw(SDL_Surface *surface)
{
	glm::vec3 parent_position = glm::vec3(0,0,0);
	glm::vec3 parent_scale = glm::vec3(0,0,0);

	parent_scale.x = surface->w;
	parent_scale.y = surface->h;
	this->draw(surface, parent_position, parent_scale);
}

void						Text::draw(SDL_Surface *surface, glm::vec3 &parent_position, glm::vec3 &parent_scale)
{
	SDL_Rect	text_position;
	SDL_Surface	*text_surface;
	glm::vec3	final_position = glm::vec3(0,0,0);


	if (this->position == TAG_POSITION_CENTER) {
		final_position.x = parent_position.x + (parent_scale.x / 2);
	} else if (this->position == TAG_POSITION_LEFT) {
		final_position.x = parent_position.x;
	} else if (this->position == TAG_POSITION_RIGHT) {
		final_position.x = parent_position.x + parent_scale.x;
	}

	text_position.x = this->transform.position.x + final_position.x;
	text_position.y = this->transform.position.y + final_position.y;

	text_surface = TTF_RenderText_Solid(this->font, this->text, this->color);
	SDL_BlitSurface(text_surface, NULL, surface, &text_position);
	SDL_FreeSurface(text_surface);
}

// PRIVATE METHOD ################################################

void						Text::initialize(const char *text, const char *style)
{
	this->text = text;
	this->color = {255, 255, 255,0};
	this->fontSize = 10;
	this->font = NULL;
	this->position = TAG_POSITION_NULL;
	this->setStyle(style);
	if (this->font == NULL) {
		this->setFontFamily("arial");
	}
}

// ###############################################################
