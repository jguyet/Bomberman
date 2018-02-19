#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

Module_h::Module_h ( void )
{
	return ;
}

Module_h::Module_h ( Module_h const & src )
{
	*this = src;
	return ;
}

Module_h &				Module_h::operator=( Module_h const & rhs )
{
	if (this != &rhs)
	{
		this->heuristic = rhs.heuristic;
		this->pos_x = rhs.pos_x;
		this->pos_y = rhs.pos_y;
	}
	return (*this);
}

Module_h::~Module_h ( void )
{
	return ;
}

bool operator<(const Module_h& lhs, const Module_h& rhs)
{
	return (lhs.heuristic < rhs.heuristic);
}

bool operator>(const Module_h& lhs, const Module_h& rhs)
{
	return (lhs.heuristic > rhs.heuristic);
}

std::ostream &				operator<<(std::ostream & o, Module_h const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################
