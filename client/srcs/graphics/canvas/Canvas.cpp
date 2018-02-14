#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Canvas::Canvas ( int width, int height )
{
	this->width = width;
	this->height = height;
	this->canvas = NULL;
	this->updated = false;
	return ;
}

Canvas::Canvas ( Canvas const & src )
{
	*this = src;
	return ;
}

Canvas &				Canvas::operator=( Canvas const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Canvas::~Canvas ( void )
{
	SDL_FreeSurface(this->canvas);
	return ;
}

std::ostream &				operator<<(std::ostream & o, Canvas const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Canvas::build(void)
{
	if (this->canvas != NULL) {
		glDeleteTextures(1, &this->textureID);
		SDL_FreeSurface(this->canvas);
	}
	this->canvas = SDL_CreateRGBSurface(0, this->width, this->height, 32, 0,0,0,0);
	SDL_FillRect(this->canvas, NULL, SDL_MapRGB(this->canvas->format, 0, 1, 0));

	for (std::map<const char*, Text*>::iterator it = this->texts.begin(); it != this->texts.end(); it++) {
		(*it).second->draw(this->canvas);
	}
	for (std::map<const char*, Image*>::iterator it = this->images.begin(); it != this->images.end(); it++) {
		(*it).second->draw(this->canvas);
	}
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, \
			this->canvas->w, this->canvas->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, this->canvas->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void						Canvas::draw(void)
{
	if (this->updated == false) {
		this->build();
	}
	//drawing
	glUseProgram(ShaderUtils::instance->get("canvas"));
	glUniform1i(Model::model["canvas"]->texUnit, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glBindVertexArray(Model::model["canvas"]->myMeshes[0].vao);
	glDrawElements(GL_TRIANGLES, Model::model["canvas"]->myMeshes[0].numFaces * 3, GL_UNSIGNED_INT, 0);
	glUseProgram(0);
}

void						Canvas::addText(const char *key, Text *text)
{
	if (this->texts.count(key) != 0) {
		Text *tmp = this->texts[key];
		this->texts.erase(key);
		delete tmp;
	}
	this->texts[key] = text;
	this->updated = false;
}

void						Canvas::addImage(const char *key, Image *img)
{
	if (this->images.count(key) != 0) {
		Image *tmp = this->images[key];
		this->images.erase(key);
		delete tmp;
	}
	this->images[key] = img;
	this->updated = false;
}

// ###############################################################
