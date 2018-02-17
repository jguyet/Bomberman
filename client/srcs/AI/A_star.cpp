#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

A_star::A_star ( void )
{
	return ;
}

A_star::A_star ( A_star const & src )
{
	*this = src;
	return ;
}

A_star &				A_star::operator=( A_star const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

A_star::~A_star ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, A_star const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						A_star::get_heuristic(void)
{
	Manhattan_h elem;

	// int dif_x = (e.x_base - finalboard[e.value as usize - 1].x_base).abs();
	// int dif_y = (e.y_base - finalboard[e.value as usize - 1].y_base).abs();
	// elem.heuristic = dif_x + dif_y;
}

void						A_star::path_finding(void)
{

}

// ###############################################################

// PRIVATE METHOD ################################################

// void						A_star::gen_test_map(int size)
// {
// 	std::vector<int> map;
// }

// ###############################################################
