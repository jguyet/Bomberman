#ifndef BOXCOLLIDER_HPP
# define BOXCOLLIDER_HPP

# include "Bomberman.hpp"

class BoxCollider : public Component
{
	public:
		static void							Check3DCollisions(std::map<long, GameObject*> &gameObjects);
											BoxCollider( glm::vec3 center, glm::vec3 size );
											BoxCollider( BoxCollider const & src );
		virtual								~BoxCollider( void );

		BoxCollider &						operator=( BoxCollider const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, BoxCollider const & i);

		glm::vec3							center;
		glm::vec3							size;
	private:
};

#endif
