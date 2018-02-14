#ifndef MAP_HPP
# define MAP_HPP

# include "Bomberman.hpp"

struct Case {
	Case(void) {
		this->ground = NULL;
		this->obstacle = NULL;
		this->walkable = false;
	}
	GameObject		*ground;
	GameObject 		*obstacle;
	bool			walkable;
	glm::vec3		position;
	//entity
};

class Map
{
	public:
		// STATICS #############################################################
		// #####################################################################
		// CANONICAL ###########################################################
													Map( Scene *scene );
													Map( Map const & src );
		virtual										~Map( void );
		Map &										operator=( Map const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, Map const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		Case										*getCase(int x, int z);
		void										build(void);
		// #####################################################################
		std::map<std::pair<float, float>, Case*>	cases;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		Scene										*scene;
		// #####################################################################
};

#endif
