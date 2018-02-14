#ifndef CANVAS_HPP
# define CANVAS_HPP

# include "graphics/canvas/Text.hpp"
# include "graphics/canvas/Image.hpp"
# include "Bomberman.hpp"

class Canvas
{
	public:

		Canvas( int width, int height );
		Canvas( Canvas const & src );
		virtual ~Canvas( void );

		Canvas &							operator=( Canvas const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Canvas const & i);

		void								draw(void);
		void								addText(const char *key, Text *text);
		void								addImage(const char *key, Image *img);

	private:
		void								build(void);
		SDL_Surface							*canvas;
		GLuint								textureID;
		int									width;
		int									height;
		bool								updated;
		std::map<const char*, Image*>		images;
		std::map<const char*, Text*>		texts;

};

#endif
