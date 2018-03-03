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
	this->elements = NULL;
	this->textureID = 0;
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
	if (this->canvas != NULL) {
		SDL_FreeSurface(this->canvas);
	}
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

	if (this->elements != NULL) {
		typedef std::function<bool(std::pair<std::string, Tag*>, std::pair<std::string, Tag*>)> Comparator;

		Comparator compFunctor = [](std::pair<std::string, Tag*> elem1 ,std::pair<std::string, Tag*> elem2)
								{
									return elem1.second->transform.position.z <= elem2.second->transform.position.z;
								};
		std::set<std::pair<std::string, Tag*>, Comparator> sorted_map(this->elements->begin(), this->elements->end(), compFunctor);

		for (std::pair<std::string, Tag*> element : sorted_map)
		{
			element.second->draw(this->canvas);
		}
	}
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, \
			this->canvas->w, this->canvas->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, this->canvas->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	this->updated = true;
}

void						Canvas::draw(void)
{
	if (this->updated == false) {
		this->build();
	}
	//drawing
	glUseProgram(ShaderUtils::getInstance()->get("canvas"));
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

void						Canvas::addSquare(const char *key, Square *square)
{
	if (this->squares.count(key) != 0) {
		Square *tmp = this->squares[key];
		this->squares.erase(key);
		delete tmp;
	}
	this->squares[key] = square;
	this->updated = false;
}

void						Canvas::setElementsMap(std::map<std::string, Tag*> *elements)
{
	this->elements = elements;
	this->updated = false;
}

// ###############################################################
