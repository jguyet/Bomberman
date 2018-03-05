#ifndef MAP_HPP
# define MAP_HPP

# include "Bomberman.hpp"
# include "models/Case.hpp"

struct MapObject {
	int id;
	std::string textureID;
	std::string type;
};

class Map
{
	public:
		// STATICS #############################################################
		// #####################################################################
		// CANONICAL ###########################################################
													Map(std::string name);
													Map( Map const & src );
		virtual										~Map( void );
		Map &										operator=( Map const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, Map const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		Case										*getCase(int x, int z);
		std::string									getName();
		// #####################################################################
		std::map<std::pair<int, int>, Case>			content;
		std::string									name;
		std::map<int, MapObject>					objects;
		std::vector<Case>							soloCases;
		std::vector<Case>							pvpCases;
		int											width;
		int											height;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		Scene										*scene;
		// #####################################################################
};

#endif
