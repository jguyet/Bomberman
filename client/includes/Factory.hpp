#ifndef FACTORY_HPP
# define FACTORY_HPP

#include "Bomberman.hpp"
#include <mutex>

class Factory
{
	public:
		static GameObject					*newBlock(std::string model);
		static GameObject					*newPlayer(int Id);
		static GameObject					*newBomb(CharacterControllerScript *playerController);
		static GameObject					*newExplosion(float x, float z, long timer);
		static GameObject					*newBackground(void);
		static GameObject					*newSkybox(void);
		static GameObject 					*newGoomba(void);

		static GameObject					*newPowerUp(float x, float z);

		Factory( void );
		Factory( Factory const & src );
		virtual ~Factory( void );

		Factory &							operator=( Factory const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Factory const & i);
};

#endif
