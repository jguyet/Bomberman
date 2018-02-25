#ifndef IMAGE_HPP
# define IMAGE_HPP

# include "Bomberman.hpp"

class Image : public Tag
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
										Image( const char *path );
										Image (const char *path, int base_width, int base_height, int width, int height);
										Image( Image const & src );
		virtual							~Image( void );
		Image &							operator=( Image const & rhs );
		friend std::ostream &			operator<<(std::ostream & o, Image const & i);
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
		SDL_Surface						*image;
		int								width = -1;
		int								height = -1;
		// ####################################################################
};

#endif
