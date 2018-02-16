#ifndef A_STAR_HPP
# define A_STAR_HPP

# include "Bomberman.hpp"

struct Manhattan_h {
	int		heuristic;
	int		pos_x;
	int		pos_y;
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
		void										get_heuristic(void);
		void										path_finding(void);
		// #####################################################################

		// #####################################################################
	private:
		// PRIVATE #############################################################
		// open list  priority_queue
		// close list std::map
		// #####################################################################
};

#endif
