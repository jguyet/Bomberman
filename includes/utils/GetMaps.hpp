#ifndef GETMAPS_HPP
# define GETMAPS_HPP

# include "Bomberman.hpp"

# include <regex>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <exception>

# define GROUND 2
# define WALL 0

class GetMaps
{
	public:
		// STATICS #############################################################

		// #####################################################################

		// CANONICAL ###########################################################
											GetMaps( void );
											GetMaps( GetMaps const & src );
		virtual								~GetMaps( void );
		GetMaps &							operator=( GetMaps const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, GetMaps const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		void				get_all_maps(std::map<std::string, std::map<std::pair<int, int>, Case>> &maps);
		void				load_map(std::string path, std::map<std::pair<int, int>, Case> &map);

		// #####################################################################
	private:
		// PRIVATE #############################################################
		int					get_dir_maps(std::map<std::string, std::map<std::pair<int, int>, Case>> &maps);
		// std::map<std::string, std::map<std::pair<int, int>, Case>> maps;
		// #####################################################################
};

#endif
