#ifndef FACTORY_HPP
# define FACTORY_HPP

#include "Bomberman.hpp"

class Factory
{
	public:
		static GameObject					*newBlock(std::string model);
		static GameObject					*newPlayer(void);
		static GameObject					*newBomb(void);
		static GameObject					*newExplosion(float x, float z);

		Factory( void );
		Factory( Factory const & src );
		virtual ~Factory( void );

		Factory &							operator=( Factory const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Factory const & i);
};

#endif
