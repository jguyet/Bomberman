#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Image::Image (std::string const &path, int base_width, int base_height, int width, int height)
{
	this->image = NULL;
	this->path = std::string(path);
	this->base_width = base_width;
	this->base_height = base_height;
	this->resized = false;
	this->loaded = false;
	this->width = width;
	this->height = height;
	this->transform.scale.x = this->width;
	this->transform.scale.y = this->height;
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
	if (this->image != NULL) {
		SDL_FreeSurface(this->image);
	}
	return ;
}

std::ostream &				operator<<(std::ostream & o, Image const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Image::load_image(void)
{
	this->image = IMG_Load(this->path.c_str());
	if (this->image == NULL) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	this->loaded = true;
}

void						Image::resize_image(void)
{
	if (this->resized != false)
		return ;
	SDL_Rect	text_position;

	text_position.x = 0;
	text_position.y = 0;
	text_position.w = this->width;
	text_position.h = this->height;

	//resize IMAGE
	SDL_Surface *p32BPPSurface = SDL_CreateRGBSurface(0,this->base_width,this->base_height,32,0,0,0,0);
	SDL_FillRect(p32BPPSurface, NULL, SDL_MapRGB(p32BPPSurface->format, 0, 1, 0));
	SDL_BlitSurface(this->image, NULL, p32BPPSurface, NULL);
	SDL_Surface *pScaleSurface = SDL_CreateRGBSurface(0,this->width,this->height,32,0,0,0,0);
	SDL_FillRect(pScaleSurface, NULL, SDL_MapRGB(pScaleSurface->format, 0, 1, 0));
	SDL_FillRect(pScaleSurface, &text_position, SDL_MapRGBA(pScaleSurface->format, 255, 0, 0, 255));
	SDL_BlitScaled(p32BPPSurface, NULL, pScaleSurface, NULL);
	SDL_FreeSurface(this->image);
	SDL_FreeSurface(p32BPPSurface);
	this->image = pScaleSurface;
	this->resized = true;
}

void						Image::setFloat(e_tag_position position)
{

}

void						Image::setFontFamily(std::string const &fontname)
{

}

void						Image::setFontSize(int font_size)
{

}

void						Image::setColor(glm::vec3 &color)
{

}

void						Image::setTextAlign(e_tag_position position)
{

}

void						Image::setBackgroundColor(glm::vec3 &color)
{

}

void						Image::setBackgroundImage(std::string const &path)
{

}

void						Image::setDisplay(bool visible)
{

}

void						Image::setStyle(std::string const &style)
{
	CSSInterpretor::interpretCSS(this, style);
}

void						Image::draw(SDL_Surface *surface)
{
	SDL_Rect	text_position;
	glm::vec3	final_position = glm::vec3(0,0,0);
	glm::vec3	final_scale = glm::vec3(0,0,0);

	if (this->loaded == false) {
		this->load_image();
	}
	if (this->image == NULL) {
		return ;
	}
	this->resize_image();

	final_position = this->getPosition(surface);

	text_position.x = final_position.x;
	text_position.y = final_position.y;

	SDL_BlitSurface(this->image, NULL, surface, &text_position);
}

bool						Image::equals(Tag *tag)
{
	Image *image = dynamic_cast<Image*>(tag);

	if (image->transform.position != this->transform.position)
		return false;
	if (image->width != this->width)
		return false;
	if (image->height != this->height)
		return false;
	return true;
}

// ###############################################################
