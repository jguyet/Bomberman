#ifndef TEXT_HPP
# define TEXT_HPP

# include "Bomberman.hpp"

class Text : public GameObject
{
	public:
		// STATICS ############################################################
		// ####################################################################
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
		void										draw(SDL_Surface *surface, glm::vec3 &parent_position);

		void										setColor(int r, int g, int b);
		void										setFont(const char *font, int size);
		void										setFont(std::string font, int size);
		void										setText(const char *text);
		void										setText(std::string text);
		void										css(const char *style);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		void										initialize(const char *text, const char *font);
		TTF_Font									*font;
		SDL_Color									color;
		const char									*text;
		std::string									saveptr;
		// ####################################################################
};

#endif
