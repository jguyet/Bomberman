#ifndef GETMAPS_HPP
# define GETMAPS_HPP

# include "Bomberman.hpp"

# include <iostream>
# include <fstream>
# include <regex>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
// # include <filesystem>

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
		void				get_all_maps(void);
		void				load_map(std::string path);

		// #####################################################################
	private:
		// PRIVATE #############################################################
		int					get_dir_maps(void);

		std::vector<std::string> maps_names;
		// #####################################################################
};

#endif
