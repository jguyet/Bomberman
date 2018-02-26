#ifndef TAG_HPP
# define TAG_HPP

# include "Bomberman.hpp"

enum e_tag_position {
	TAG_POSITION_LEFT,
	TAG_POSITION_RIGHT,
	TAG_POSITION_CENTER,
	TAG_POSITION_NULL
};

class Tag : public GameObject
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											Tag( void );
											Tag( Tag const & src );
		virtual								~Tag( void );
		Tag &								operator=( Tag const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Tag const & i);
		// ####################################################################
		//object
		void								setPosition(glm::vec3 &pos);
		void								setWidth(int width);
		void								setHeight(int height);

		virtual void						setFloat(e_tag_position position);
		//font
		virtual void						setColor(glm::vec3 &color);
		virtual void						setFontFamily(const char *fontname);
		virtual void						setFontSize(int font_size);
		virtual void						setTextAlign(e_tag_position position);

		//others
		virtual void						setBackgroundColor(glm::vec3 &color);
		virtual void						setBackgroundImage(const char *path);
		virtual void						setDisplay(bool visible);

		//drawing
		virtual void						draw(SDL_Surface *surface);
		virtual void						draw(SDL_Surface *surface, glm::vec3 &parent_position);

		//css updating
		virtual void						setStyle(const char *style);
		// ####################################################################
		Tag									*parent = NULL;
		e_tag_position						position;
	private:
		// PRIVATES ###########################################################
		// ####################################################################
};

#endif
