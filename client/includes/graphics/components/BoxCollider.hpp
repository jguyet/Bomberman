#ifndef BOXCOLLIDER_HPP
# define BOXCOLLIDER_HPP

# include "Bomberman.hpp"

# include <unordered_map>

class BoxCollider : public Component
{
	public:
		// STATICS ############################################################
		static void							Check3DCollisions(std::unordered_map<long, GameObject*> const &gameObjects);
		// ####################################################################
		// CANONICAL ##########################################################
											BoxCollider( glm::vec3 center, glm::vec3 size );
											BoxCollider( BoxCollider const & src );
		virtual								~BoxCollider( void );
		BoxCollider &						operator=( BoxCollider const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, BoxCollider const & i);
		// PUBLICS ############################################################
		glm::vec3							center;
		glm::vec3							size;
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		// ####################################################################
};

#endif
