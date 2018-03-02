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

		glm::vec3 const						getPosition(SDL_Surface *surface);
		glm::vec3 const						getScale(void);

		virtual void						setFloat(e_tag_position position);
		virtual void						setParent(Tag *parent);
		//font
		virtual void						setColor(glm::vec3 &color);
		virtual void						setFontFamily(std::string const &fontname);
		virtual void						setFontSize(int font_size);
		virtual void						setTextAlign(e_tag_position position);

		//others
		virtual void						setBackgroundColor(glm::vec3 &color);
		virtual void						setBackgroundImage(std::string const &path);
		virtual void						setDisplay(bool visible);
		virtual void						setValue(std::string const &value);

		//drawing
		virtual void						draw(SDL_Surface *surface);

		//css updating
		virtual void						setStyle(std::string const &style);
		// ####################################################################
		Tag									*parent = NULL;
		glm::vec3							parent_position;
		glm::vec3							parent_scale;
		e_tag_position						position;
	private:
		// PRIVATES ###########################################################
		// ####################################################################
};

#endif
