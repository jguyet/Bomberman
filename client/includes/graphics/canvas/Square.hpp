#ifndef SQUARE_HPP
# define SQUARE_HPP

# include "Bomberman.hpp"

class Square : public Tag
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											Square( int x, int y, int width, int height );
											Square( Square const & src );
		virtual								~Square( void );
		Square &							operator=( Square const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Square const & i);
		// ####################################################################
		// PUBLICS ############################################################
		void								setFloat(e_tag_position position);
		void								setFontFamily(const char *fontname);
		void								setFontSize(int font_size);
		void								setColor(glm::vec3 &color);
		void								setTextAlign(e_tag_position position);
		void								setBackgroundColor(glm::vec3 &color);
		void								setBackgroundImage(const char *path);
		void								setDisplay(bool visible);
		void								setStyle(const char *style);
		void								draw(SDL_Surface *surface);
		void								draw(SDL_Surface *surface, glm::vec3 &parent_position);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		void								initialize( int x, int y, int width, int height );
		SDL_Color							color;
		// ####################################################################
};

#endif
