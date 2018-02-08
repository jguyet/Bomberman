#ifndef FACTORY_HPP
# define FACTORY_HPP

#include "Bomberman.hpp"

class Factory
{
	public:
		static GameObject					*newBlock(void);
		static GameObject					*newPlayer(void);

		Factory( void );
		Factory( Factory const & src );
		virtual ~Factory( void );

		Factory &							operator=( Factory const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Factory const & i);
};

#endif
