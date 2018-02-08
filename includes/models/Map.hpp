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

class Map : public IModel
{
	public:
		// STATICS #############################################################
		// #####################################################################
		// CANONICAL ###########################################################
											Map( void );
											Map( Map const & src );
		virtual								~Map( void );
		Map &								operator=( Map const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Map const & i);
		// #####################################################################
		// @OVERRIDE IModel ####################################################
		void								render(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix);
		// GameObject						gameObject;
		// #####################################################################
		// PUBLIC ##############################################################
		Case								*getCase(int x, int z);
		// #####################################################################
		std::map<std::pair<float, float>, Case*>	cases;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		// #####################################################################
};

#endif
