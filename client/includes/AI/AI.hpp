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
													AI(GameObject* my_player);
													AI( AI const & src );
		virtual										~AI( void );
		AI &										operator=( AI const & rhs );
		// friend bool									operator<(const AI& lhs, const AI& rhs);
		// friend bool									operator>(const AI& lhs, const AI& rhs);
		friend std::ostream &						operator<<(std::ostream & o, AI const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		int											brain();
		void										get_target(float x, float y, std::vector<GameObject*> players);
		void										select_target(void);
		int											bombcol(int x, int y, int next_x, int next_y);
		// #####################################################################
		Module_h 									target;
		float										last_pos_x;
		float										last_pos_y;
		long										t_last_move;
		long										pause;
		GameObject*									tplayer;
		GameObject*									my_player;

		std::list<Module_h> 						moves;
		A_star										a_star;
		bool										select_t;
		e_action									action;

		std::vector<GameObject*> 					Objects;
		std::vector<BombControllerScript*>			bomb_l;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		void										restart_target_pos(e_action action);
		int											start_checks(void);
		// #####################################################################
};

#endif
