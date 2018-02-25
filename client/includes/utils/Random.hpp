#ifndef RANDOM_HPP
# define RANDOM_HPP

#include "Bomberman.hpp"
#include <stdlib.h>
#include <time.h>

class Random
{
	public:

		Random();
		Random( Random const & src );
		virtual ~Random();

		Random &							operator=( Random const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Random const & i);
		int					getRandom(int min, int max);
};

#endif
