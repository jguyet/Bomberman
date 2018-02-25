#ifndef CANVAS_HPP
# define CANVAS_HPP

# include "graphics/canvas/Tag.hpp"
# include "graphics/canvas/Text.hpp"
# include "graphics/canvas/Image.hpp"
# include "graphics/canvas/Square.hpp"
# include "graphics/canvas/Button.hpp"
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
		void								addSquare(const char *key, Square *square);
		void								addButton(const char *key, Button *button);
		void								setElementsMap(std::map<std::string, Tag*> *elements);

	private:
		void								build(void);
		SDL_Surface							*canvas;
		GLuint								textureID;
		int									width;
		int									height;
		bool								updated;
		std::map<const char*, Image*>		images;
		std::map<const char*, Text*>		texts;
		std::map<const char*, Square*>		squares;
		std::map<const char*, Button*>		buttons;
		std::map<std::string, Tag*>			*elements;
};

#endif
