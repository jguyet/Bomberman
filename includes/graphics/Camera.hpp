#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "Bomberman.hpp"
# include "graphics/GameObject.hpp"

class Camera
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											Camera( void );
											Camera( glm::vec3 &position, glm::vec3 &rotation );
											Camera( Camera const & src );
		virtual								~Camera( void );

		Camera &							operator=( Camera const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Camera const & i);
		// ####################################################################
		// PUBLICS ############################################################
		void								setProjection(float fov, float width, float height, float zNear, float zFar);
		void								buildLookAtProjection( glm::vec3 to );
		void								buildFPSProjection( void );
		void								move(glm::vec3 const &toDirection);
		void								UpdateView();
		void								MouseMove(glm::vec2 &lastMousePosition, glm::vec2 &mousePosition);

		glm::mat4							modelviewprojectionMatrix;
		glm::mat4							projectionMatrix;
		glm::mat4							viewMatrix;
		glm::mat4							modelMatrix;
		glm::vec3							lookAt;
		Transform							transform;
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		float								zNear;//vision de depart
		float								zFar;//vision max
		float								width;
		float								height;
		float								fov;//angle de vision
		// ####################################################################
};

#endif
