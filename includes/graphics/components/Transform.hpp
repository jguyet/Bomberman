#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include "Bomberman.hpp"

class Transform
{
	public:
		// STATICS ############################################################
		// ####################################################################

		// CANONICAL ##########################################################
									Transform( void );
									Transform( Transform const & src );
		virtual						~Transform( void );
		Transform &					operator=( Transform const & rhs );
		friend std::ostream &		operator<<(std::ostream & o, Transform const & i);
		// ####################################################################

		// PUBLICS ############################################################
		glm::mat4					enableProjectionTransformation( void );
		void						setProjection(float fov, float width, float height, float zNear, float zFar);
		glm::vec3					*getTranslation( void );
		void						setTranslation(float x, float y, float z);
		glm::vec3					*getRotation( void );
		void						setRotation(float x, float y, float z);
		glm::vec3					*getScale( void );
		void						setScale(float x, float y, float z);
		Camera						*getCamera( void );
		void						setCamera(Camera *camera);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		float								zNear;//vision de depart
		float								zFar;//vision max
		float								width;
		float								height;
		float								fov;//angle de vision
		glm::vec3							*translation;
		glm::vec3							*rotation;
		glm::vec3							*scale;
		Camera								*camera;
		// ####################################################################
};

#endif
