#ifndef TEXT_HPP
# define TEXT_HPP

# include "Bomberman.hpp"

class Text : public Tag
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											Text (std::string const &text, std::string const &style);
											Text (int number, std::string const &style);
											Text( Text const & src );
		virtual								~Text( void );
		Text &								operator=( Text const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Text const & i);
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
		void								setValue(std::string const &value);
		void								draw(SDL_Surface *surface);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		void								initialize(const char *text, std::string const &font);
		TTF_Font							*font;
		SDL_Color							color;
		const char							*text;
		std::string							saveptr;

		std::string							fontName;
		int									fontSize;
		// ####################################################################
};

#endif
