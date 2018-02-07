#ifndef MAP_HPP
# define MAP_HPP

# include "Bomberman.hpp"

struct Case {
	unsigned int 	id;
	Block 			*ground;
	Block 			*obstacle;
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
		// #####################################################################
		std::map<unsigned int, Case*>		cases;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		// #####################################################################
};

#endif
