#ifndef TEXT_HPP
# define TEXT_HPP

# include "Bomberman.hpp"

class Text : public GameObject
{
	public:
		// STATICS ############################################################
		// ####################################################################
		static std::map<const char *, TTF_Font *>	text_fonts;
		static void									addFont(const char *key, const char *path);
		// CANONICAL ##########################################################
													Text(const char *text);
													Text(std::string text);
													Text (int number);
													Text( Text const & src );
		virtual										~Text( void );
		Text &										operator=( Text const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, Text const & i);
		// ####################################################################
		// PUBLICS ############################################################
		void										draw(SDL_Surface *surface);

		void										setColor(int r, int g, int b);
		void										setFont(const char *font);
		void										setFont(std::string font);
		void										setText(const char *text);
		void										setText(std::string text);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		void										initialize(const char *text);
		TTF_Font									*font;
		SDL_Color									color;
		const char									*text;
		std::string									saveptr;
		// ####################################################################
};

#endif
