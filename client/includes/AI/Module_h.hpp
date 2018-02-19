#ifndef MODULE_H_HPP
# define MODULE_H_HPP

# include "Bomberman.hpp"
# include <queue>

class Module_h
{
	public:
		// STATICS #############################################################
		// #####################################################################
		// CANONICAL ###########################################################
													Module_h( void );
													Module_h( Module_h const & src );
		virtual										~Module_h( void );
		Module_h &									operator=( Module_h const & rhs );
		friend bool									operator<(const Module_h& lhs, const Module_h& rhs);
		friend bool									operator>(const Module_h& lhs, const Module_h& rhs);
		friend std::ostream &						operator<<(std::ostream & o, Module_h const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		// #####################################################################
		int		pos_x;
		int		pos_y;
		int		heuristic;
		int		p;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		// #####################################################################
};

#endif
