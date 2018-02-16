#include "Bomberman.hpp"

// STATIC ########################################################

std::map<const char *, TTF_Font *> Text::text_fonts = std::map<const char *, TTF_Font *>();

void							Text::addFont(const char *key, const char *path)
{
	if (Text::text_fonts.count(key) == 0) {
		Text::text_fonts[key] = TTF_OpenFont(path, 30);
	}
}

// ###############################################################

// CANONICAL #####################################################

Text::Text (const char *text) : GameObject()
{
	this->initialize(text);
	return ;
}

Text::Text (std::string text) : GameObject()
{
	this->saveptr = text;
	this->initialize(this->saveptr.c_str());
	return ;
}

Text::Text (int number) : GameObject()
{
	this->saveptr = (std::ostringstream() << number).str();
	this->initialize(this->saveptr.c_str());
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

void								Text::setColor(int r, int g, int b)
{
	this->color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b),0};
}

void								Text::setFont(const char *font)
{
	if (Text::text_fonts.count(font) == 0) {
		Text::addFont(font, (std::ostringstream() << "assets/fonts/" << font).str().c_str());
	}
	this->font = Text::text_fonts[font];
}

void								Text::setFont(std::string font)
{
	this->setFont(font.c_str());
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
	SDL_Rect	text_position;
	SDL_Surface	*text_surface;

	text_position.x = this->transform.position.x;
	text_position.y = this->transform.position.y;

	text_surface = TTF_RenderText_Solid(this->font, this->text, this->color);
	SDL_BlitSurface(text_surface, NULL, surface, &text_position);
	SDL_FreeSurface(text_surface);
}

// PRIVATE METHOD ################################################

void						Text::initialize(const char *text)
{
	this->text = text;
	this->color = {255, 255, 255,0};
	if (Text::text_fonts.count("arial") == 0) {
		Text::addFont("arial", "assets/fonts/arial.ttf");
	}
	this->font = Text::text_fonts["arial"];
}

// ###############################################################
