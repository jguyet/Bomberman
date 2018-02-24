#ifndef BUTTON_HPP
# define BUTTON_HPP

# include "graphics/keys/KeyBoard.hpp"
# include "Bomberman.hpp"

enum e_text_position {
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};

class Button : public GameObject, public KeyBoardEventHandler
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											Button ( Text *text, int x, int y, int width, int height);
											Button ( Text *text, e_text_position position, int x, int y, int width, int height );
											Button( Button const & src );
		virtual								~Button( void );
		Button &							operator=( Button const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Button const & i);
		// ####################################################################
		void								handleUP(unsigned int key);
		void								handleDOWN(unsigned int key);
		void								handleRELEASE(unsigned int key);
		// PUBLICS ############################################################
		void								addTexture(Image *image);
		void								draw(SDL_Surface *surface);
		void								css(const char *css);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		void								initialize(Image *image, Text *text, e_text_position position, int x, int y, int width, int height);
		Image								*image;
		Square								*background;
		Text								*text;
		e_text_position						text_position = TEXT_CENTER;
		// ####################################################################
};

#endif
