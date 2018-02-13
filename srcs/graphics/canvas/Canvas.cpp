#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Canvas::Canvas ( int width, int height )
{
	this->width = width;
	this->height = height;
	this->canvas = SDL_CreateRGBSurface(0, this->width, this->height, 32, 0,0,0,0);
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
	return ;
}

std::ostream &				operator<<(std::ostream & o, Canvas const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Canvas::draw(void)
{
	//create texture by canvas surface
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, \
			this->canvas->w, this->canvas->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, this->canvas->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//drawing
	glUseProgram(ShaderUtils::instance->get("canvas"));
	glUniform1i(Model::model["canvas"]->texUnit, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glBindVertexArray(Model::model["canvas"]->myMeshes[0].vao);
	glDrawElements(GL_TRIANGLES, Model::model["canvas"]->myMeshes[0].numFaces * 3, GL_UNSIGNED_INT, 0);
	glUseProgram(0);

	//free
	glDeleteTextures(1, &this->textureID);
	SDL_FreeSurface(this->canvas);
	this->canvas = SDL_CreateRGBSurface(0, this->width, this->height, 32, 0,0,0,0);
}

void						Canvas::addText(Text &text)
{
	text.draw(this->canvas);
}

void						Canvas::addImage(Image &img)
{
	img.draw(this->canvas);
}

// void						Canvas::addText(const char *str, glm::vec2 &position, TTF_font *font, SDL_Color &color)
// {
// 	//SDL_Color color = {255, 255, 255,0};//white
// 	// SDL_Surface	*text_surface;
//     //
// 	// text_surface = TTF_RenderText_Solid(font, text, color);
// 	// SDL_BlitSurface(text_surface, NULL, canvas, &text_position);
// 	// SDL_FreeSurface(text_surface);
// }

// ###############################################################
