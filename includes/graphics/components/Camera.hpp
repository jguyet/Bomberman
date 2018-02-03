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
									Camera( glm::vec3 &position, glm::vec3 &rotation );
									Camera( Camera const & src );
		virtual						~Camera( void );

		Camera &					operator=( Camera const & rhs );
		friend std::ostream &		operator<<(std::ostream & o, Camera const & i);
		// ####################################################################

		// PUBLICS ############################################################
		// types de projections :
		void						buildLookAtProjection( void );
		void						buildFPSProjection( void );

		void						setProjection(float fov, float width, float height, float zNear, float zFar);

		//Look at functions
		void						setLookAt(float x, float y, float z);
		void						setLookAt(glm::vec3 const &v);
		glm::vec3					&getLookAt( void );

		void						setPosition(float x, float y, float z);
		void						setPosition(glm::vec3 const &v);
		glm::vec3					&getPosition( void );

		void						setDirection(float x, float y, float z);
		void						setDirection(glm::vec3 const &v);
		glm::vec3					&getDirection( void );

		glm::vec3					&getRotation( void );
		void						setRotation(glm::vec3 const &v);
		void						setRotation(float x, float y, float z);

		void						move(glm::vec3 const &toDirection);
		void						UpdateView();
		void						MouseMove(int x, int y);
		// ####################################################################

		glm::vec3							right;
		glm::vec3							up;
		glm::vec2							mousePosition;
		glm::mat4							modelviewprojectionMatrix;
		glm::mat4							projectionMatrix;
		glm::mat4							viewMatrix;
		glm::mat4							modelMatrix;
	private:
		// PRIVATES ###########################################################
		float								zNear;//vision de depart
		float								zFar;//vision max
		float								width;
		float								height;
		float								fov;//angle de vision
		glm::vec3							position;
		glm::vec3							direction;
		glm::vec3							rotation;
		glm::vec3							lookAt;
		// ####################################################################
};

#endif
