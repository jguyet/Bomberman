#ifndef MAP_HPP
# define MAP_HPP

# include "Bomberman.hpp"
# include "models/Case.hpp"

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
		std::map<std::pair<int, int>, Case>			getContent();
		// #####################################################################
		std::map<std::pair<int, int>, Case>			content;
		std::string									name;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		Scene										*scene;
		// #####################################################################
};

#endif
