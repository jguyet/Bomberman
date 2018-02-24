#ifndef BUTTON_HPP
# define BUTTON_HPP

# include "graphics/keys/KeyBoard.hpp"
# include "Bomberman.hpp"

enum e_text_position {
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};

class Button : public Tag
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											Button ( const char *text, const char *style );
											Button ( std::string text, const char *style );
											Button( Button const & src );
		virtual								~Button( void );
		Button &							operator=( Button const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Button const & i);
		// ####################################################################
		// TAG Override #######################################################
		void								setFloat(e_float_position position);
		void								setFontFamily(const char *fontname);
		void								setFontSize(int font_size);
		void								setColor(glm::vec3 &color);
		void								setTextAlign(e_float_position position);
		void								setBackgroundColor(glm::vec3 &color);
		void								setBackgroundImage(const char *path);
		void								setDisplay(bool visible);
		void								setStyle(const char *style);
		void								draw(SDL_Surface *surface);
		void								draw(SDL_Surface *surface, glm::vec3 &parent_position);
		// ####################################################################
		// PUBLICS ############################################################
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		void								initialize(Text *text);
		Image								*image;
		Square								*background;
		Text								*text;
		e_text_position						text_position = TEXT_CENTER;
		// ####################################################################
};

#endif
