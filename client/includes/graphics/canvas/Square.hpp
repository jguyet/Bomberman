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
		void								setFontFamily(std::string const &fontname);
		void								setFontSize(int font_size);
		void								setColor(glm::vec3 &color);
		void								setTextAlign(e_tag_position position);
		void								setBackgroundColor(glm::vec3 &color);
		void								setBackgroundImage(std::string const &path);
		void								setDisplay(bool visible);
		void								setStyle(std::string const &style);
		void								draw(SDL_Surface *surface);
		bool								equals(Tag *tag);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		void								initialize( int x, int y, int width, int height );
		SDL_Color							color;
		// ####################################################################
};

#endif
