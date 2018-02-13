#ifndef CANVAS_HPP
# define CANVAS_HPP

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
		void								addText(Text &text);
		void								addImage(Image &img);

	private:
		SDL_Surface							*canvas;
		GLuint								textureID;
		int									width;
		int									height;

};

#endif
