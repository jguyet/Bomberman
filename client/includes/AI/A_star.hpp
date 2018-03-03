#ifndef A_STAR_HPP
# define A_STAR_HPP

# include "Bomberman.hpp"
# include <queue>

enum e_action {
	ATTACK,
	SEARCH,
	WAIT,
	ESCAPE,
	IDLE
};

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
		bool										path_finding(int y, int x,
			Module_h &target, std::list<Module_h> &moves,
			std::vector<BombControllerScript*> &bomb_l, e_action action);
		void										set_map(Map* map);
		int											bomb_col(std::vector<BombControllerScript*> bomb_l, float x, float y);
		// #####################################################################
		Map* 										map;
		Module_h									start;
		std::vector<BombControllerScript*>			bomb_list;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		int											Find_next(std::list<Module_h> &moves, int x, int y, int p, int s_x, int s_y);
		int											FormatMoves(std::list<Module_h> &moves, int x, int y, int p, int s_x, int s_y);
		int											get_heuristic(int y, int x, Module_h &target, int p);
		void										get_adjacent(Module_h &c_case, Module_h &target, int x, int y, int p);
		void										find_path(Module_h &target, e_action action);
		int											stop_condition(Module_h &c_case, Module_h &target, e_action action);
		void										delete_lists(void);
		void										init_var(int &x, int &y, Module_h &target, e_action action);
		// #####################################################################
		std::priority_queue<Module_h, std::vector<Module_h>, std::greater<Module_h>>	open_list;
		std::map<std::pair<int, int>, Module_h>											close_list;
		// #####################################################################
};

#endif
