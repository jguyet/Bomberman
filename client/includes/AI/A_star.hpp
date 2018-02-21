#ifndef A_STAR_HPP
# define A_STAR_HPP

# include "Bomberman.hpp"
# include <queue>

class A_star
{
	public:
		// STATICS #############################################################
		// #####################################################################
		// CANONICAL ###########################################################
													A_star( void );
													A_star( A_star const & src );
		virtual										~A_star( void );
		A_star &									operator=( A_star const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, A_star const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		bool										path_finding(int y, int x, Module_h &target, std::list<Module_h> &moves);
		void										set_map(Map* map);
		// #####################################################################
		Map* 										map;
		// Module_h									last_move;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		int											Find_next(std::list<Module_h> &moves, int x, int y, int p, int s_x, int s_y);
		int											FormatMoves(std::list<Module_h> &moves, int x, int y, int p, int s_x, int s_y);
		int											get_heuristic(int y, int x, Module_h &target, int p);
		void										find_path(Module_h &target);
		void										get_adjacent(Module_h c_case, Module_h &target, int x, int y, int p);
		// #####################################################################
		std::priority_queue<Module_h, std::vector<Module_h>, std::greater<Module_h>>	open_list;
		std::map<std::pair<int, int>, Module_h>											close_list;
		// #####################################################################
};

#endif
