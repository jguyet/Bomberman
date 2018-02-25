#ifndef MAPMANAGER_HPP
# define MAPMANAGER_HPP

# include <ostream>
# include "Bomberman.hpp"
# include "models/Map.hpp"
# include <regex>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <exception>
# include "utils/Random.hpp"

# define GROUND 2
# define WALL 0

class MapManager
{
	public:
		MapManager(Scene *scene);
		MapManager(void);
		MapManager( MapManager const & src );
		virtual ~MapManager();

		MapManager &							operator=( MapManager const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, MapManager const & i);

		void			loadMaps();
		void			readMaps();
		void			parseMaps(std::string name, std::map<std::pair<int, int>, Case> &map);
		int				setBlock(std::map<std::pair<int, int>, Case> &map, int x, int y, int value);
		Map				*getMap(std::string name);
		void			buildObjects(Map *selected);
		Case			*getRandomWalkableCase(Map *from);
	private:
		static	std::map<std::string, Map*> maps;
		Scene								*scene;
};

#endif
