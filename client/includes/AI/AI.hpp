#ifndef AI_HPP
# define AI_HPP

# include "Bomberman.hpp"
# include <queue>

class AI
{
	public:
		// STATICS #############################################################
		// #####################################################################
		// CANONICAL ###########################################################
													AI( void );
													AI( AI const & src );
		virtual										~AI( void );
		AI &										operator=( AI const & rhs );
		// friend bool									operator<(const AI& lhs, const AI& rhs);
		// friend bool									operator>(const AI& lhs, const AI& rhs);
		friend std::ostream &						operator<<(std::ostream & o, AI const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		void										get_target(int x, int y, std::vector<GameObject*> players);
		int											brain(int x, int y);
		// #####################################################################
		Module_h 									target;
		GameObject*									tplayer;

		bool										select_t;
		std::list<Module_h> 						moves;
		A_star										a_star;
		int											last_move;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		// #####################################################################
};

#endif
