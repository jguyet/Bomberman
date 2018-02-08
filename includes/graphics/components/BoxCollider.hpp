#ifndef BOXCOLLIDER_HPP
# define BOXCOLLIDER_HPP

# include "Bomberman.hpp"

class BoxCollider : public Component
{
	public:
											BoxCollider( void );
											BoxCollider( BoxCollider const & src );
		virtual								~BoxCollider( void );

		BoxCollider &						operator=( BoxCollider const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, BoxCollider const & i);

		glm::vec3							center;
		glm::vec3							size;
		void								(*m)(GameObject *obj, GameObject *wall);
	private:
};

#endif
