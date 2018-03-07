#ifndef SAVEMANAGER_HPP
# define SAVEMANAGER_HPP

#include "Bomberman.hpp"
#define MAP_NAME_LEN 256

#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <unistd.h>

struct SaveObject
{
	char map_name[MAP_NAME_LEN];
};

class SaveManager
{
	public:
		SaveManager();
		SaveManager( SaveManager const & src );
		virtual ~SaveManager();

		void		save(std::string);
		SaveObject	*loadSave();
		int			getCurrentLevel();
		void		loadNextLevel();
		void		levelToMap(std::string &get, int level);
		void 		levelUP(void);
		int			mapToLevel(std::string map);

		SaveManager &							operator=( SaveManager const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, SaveManager const & i);

		SaveObject		*saveObject;
		std::string		save_file;
};

#endif
