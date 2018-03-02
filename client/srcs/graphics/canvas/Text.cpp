#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

Text::Text (std::string const &text, std::string const &style)
{
	this->saveptr = std::string(text);
	this->initialize(this->saveptr.c_str(), style);
	return ;
}

Text::Text (int number, std::string const &style)
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

void						Text::setFontFamily(std::string const &fontname)
{
	std::ostringstream s;
	std::ostringstream sfontName;

	if (fontname == "")
		return ;
	sfontName << fontname << "_" << this->fontSize;
	this->fontName = sfontName.str();
	if (BombermanClient::getInstance()->fonts.count(sfontName.str()))
	{
		this->font = BombermanClient::getInstance()->fonts[sfontName.str()];
		return ;
	}
	s << "assets/fonts/" << split(this->fontName, '_').at(0) << ".ttf";
	std::string font_path = s.str();
	std::ifstream ifs(font_path.c_str());
	if (!ifs) {
		std::cerr << "font " << font_path << " doens't exists." << std::endl;
		return ;
	}
	this->font = TTF_OpenFont(font_path.c_str(), this->fontSize);
	BombermanClient::getInstance()->fonts[sfontName.str()] = this->font;
}

void						Text::setFontSize(int font_size)
{
	if (this->fontSize == font_size)
		return ;
	this->fontSize = font_size;
	if (this->font != NULL)
	{
		std::string fname = split(this->fontName, '_').at(0);
		this->setFontFamily(fname.c_str());
	}
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

void						Text::setBackgroundImage(std::string const &path)
{

}

void						Text::setDisplay(bool visible)
{

}

void						Text::setStyle(std::string const &style)
{
	CSSInterpretor::interpretCSS(this, style);
}

void						Text::setValue(std::string const &value)
{
	this->text = value.c_str();
}

void						Text::draw(SDL_Surface *surface)
{
	SDL_Rect	text_position;
	SDL_Surface	*text_surface;
	glm::vec3	final_position = glm::vec3(0,0,0);

	if (this->font == NULL)
		return ;
	final_position = this->getPosition(surface);
	text_position.x = final_position.x;
	text_position.y = final_position.y;
	text_surface = TTF_RenderText_Solid(this->font, this->text, this->color);
	SDL_BlitSurface(text_surface, NULL, surface, &text_position);
	SDL_FreeSurface(text_surface);
}

// PRIVATE METHOD ################################################

void						Text::initialize(const char *text, std::string const &style)
{
	this->text = text;
	this->color = {255, 255, 255,0};
	this->fontSize = 10;
	this->font = NULL;
	this->setStyle(style);
	if (this->font == NULL) {
		this->setFontFamily("arial");
	}
}

// ###############################################################
