#ifndef TEXT_HPP
# define TEXT_HPP

# include "Bomberman.hpp"

class Text : public Tag
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											Text(const char *text, const char *style);
											Text(std::string text, const char *style);
											Text (int number, const char *style);
											Text( Text const & src );
		virtual								~Text( void );
		Text &								operator=( Text const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Text const & i);
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
		void								draw(SDL_Surface *surface, glm::vec3 &parent_position, glm::vec3 &parent_scale);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		void								initialize(const char *text, const char *font);
		TTF_Font							*font;
		SDL_Color							color;
		const char							*text;
		std::string							saveptr;

		e_tag_position						position;

		std::string							fontName;
		int									fontSize;
		// ####################################################################
};

#endif
