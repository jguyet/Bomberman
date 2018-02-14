#ifndef IMAGE_HPP
# define IMAGE_HPP

# include "Bomberman.hpp"

class Image : public GameObject
{
	public:

		Image( const char *path );
		Image( Image const & src );
		virtual ~Image( void );

		Image &							operator=( Image const & rhs );
		friend std::ostream &			operator<<(std::ostream & o, Image const & i);

		void							draw(SDL_Surface *surface);
	private:
		SDL_Surface						*image;
};

#endif
