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

# define GROUND_POSITION_HEIGHT 2
# define WALL_POSITION_HEIGHT 0

class MapManager
{
	public:
		MapManager(Scene *scene, std::string const &map_name);
		MapManager(void);
		MapManager( MapManager const & src );
		virtual ~MapManager();

		MapManager &							operator=( MapManager const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, MapManager const & i);

		bool				loadMap( void );
		bool				parseMap(Map *map, std::string const &content);
		Map					*getMap(void);
		void				buildObjects(void);

		std::vector<Case*>	getAllDestructibleCases(void);
		std::vector<Case*>	getAllIndestructibleCases(void);

		Case				*getRandomWalkableSoloCase(void);
		Case				*getRandomWalkablePvPCase(void);

		bool				addGroundToCase( Case &case_ref, std::string const &objectID );
		bool				addDestructibleToCase( Case &case_ref, std::string const &objectID );
		bool				addIndestructibleToCase( Case &case_ref, std::string const &objectID );
		bool				addAIToCase( Case &case_ref, std::string const &objectID );
		bool				addPvPCase( Case &case_ref, std::string const &objectID );
		bool				addSoloCase( Case &case_ref, std::string const &objectID );


	private:
		Map									*map;
		std::string							map_path;
		std::string							map_name;
		std::string							content;
		Scene								*scene;

		typedef bool (MapManager::*LexerObjectsTypesMethods)( Case &case_ref, std::string const &objectID );
		std::map<std::string, LexerObjectsTypesMethods>	map_lexer_types;
};

#endif
