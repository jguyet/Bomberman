#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Image::Image (const char *path)
{
	this->image = IMG_Load(path);
	if (this->image == NULL) {
		printf("IMG_Load: %s\n", IMG_GetError());
		return ;
	}
	return ;
}

Image::Image (const char *path, int base_width, int base_height, int width, int height)
{
	SDL_Rect	text_position;

	text_position.x = 0;
	text_position.y = 0;
	text_position.w = width;
	text_position.h = height;

	this->image = IMG_Load(path);
	if (this->image == NULL) {
		printf("IMG_Load: %s\n", IMG_GetError());
		return ;
	}
	this->width = width;
	this->height = height;
	//resize IMAGE
	SDL_Surface *p32BPPSurface = SDL_CreateRGBSurface(0,base_width,base_height,32,0,0,0,0);
	SDL_BlitSurface(this->image, NULL, p32BPPSurface, NULL);
	SDL_Surface *pScaleSurface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
	SDL_FillRect(pScaleSurface, &text_position, SDL_MapRGBA(pScaleSurface->format, 255, 0, 0, 255));
	SDL_BlitScaled(p32BPPSurface, NULL, pScaleSurface, NULL);
	SDL_FreeSurface(this->image);
	SDL_FreeSurface(p32BPPSurface);
	this->image = pScaleSurface;
	return ;
}

Image::Image ( Image const & src )
{
	*this = src;
	return ;
}

Image &				Image::operator=( Image const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Image::~Image ( void )
{
	SDL_FreeSurface(this->image);
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Image const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Image::draw(SDL_Surface *surface)
{
	SDL_Rect	text_position;

	text_position.x = this->transform.position.x;
	text_position.y = this->transform.position.y;

	SDL_BlitSurface(this->image, NULL, surface, &text_position);
}

void						Image::draw(SDL_Surface *surface, glm::vec3 &parent_position)
{
	SDL_Rect	text_position;

	text_position.x = this->transform.position.x + parent_position.x;
	text_position.y = this->transform.position.y + parent_position.y;

	SDL_BlitSurface(this->image, NULL, surface, &text_position);
}

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
