#ifndef TEXT_HPP
# define TEXT_HPP

# include "Bomberman.hpp"

class Text : public GameObject
{
	public:
		static std::map<const char *, TTF_Font *> text_fonts;
		static void							addFont(const char *key, const char *path);

		Text(const char *text);
		Text(std::string text);
		Text (int number);
		Text( Text const & src );
		virtual ~Text( void );

		Text &								operator=( Text const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Text const & i);

		void								draw(SDL_Surface *surface);

	private:
		void								initialize(const char *text);
		TTF_Font							*font;
		SDL_Color							color;
		const char							*text;
		std::string							saveptr;
};

#endif
