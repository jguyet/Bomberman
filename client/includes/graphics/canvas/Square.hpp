#ifndef SQUARE_HPP
# define SQUARE_HPP

# include "Bomberman.hpp"

class Square : public GameObject
{
	public:

		Square( int x, int y, int width, int height );
		Square( Square const & src );
		virtual ~Square( void );

		Square &							operator=( Square const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Square const & i);

		void								setColor(int r, int g, int b);

		void								draw(SDL_Surface *surface);

	private:
		void								initialize( int x, int y, int width, int height );
		SDL_Color							color;
};

#endif
