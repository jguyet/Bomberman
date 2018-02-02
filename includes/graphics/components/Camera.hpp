#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "Bomberman.hpp"

class Camera
{
	public:
		// STATICS ############################################################
		// ####################################################################

		// CANONICAL ##########################################################
									Camera( void );
									Camera( glm::vec3 *position, glm::vec3 *rotation );
									Camera( Camera const & src );
		virtual						~Camera( void );

		Camera &					operator=( Camera const & rhs );
		friend std::ostream &		operator<<(std::ostream & o, Camera const & i);
		// ####################################################################

		// PUBLICS ############################################################
		void						translate(float x, float y, float z);
		void						setPosition(float x, float y, float z);
		glm::vec3					*getPosition( void );
		void						setDirection(float x, float y, float z);
		glm::vec3					*getDirection( void );
		glm::vec3					*getRotation( void );
		void						setRotation(float x, float y, float z);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		glm::vec3							*position;
		glm::vec3							*direction;
		glm::vec3							*rotation;
		// ####################################################################
};

#endif
