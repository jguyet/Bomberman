#ifndef FACTORY_HPP
# define FACTORY_HPP

#include "Bomberman.hpp"
#include <mutex>

class Factory
{
	public:
		static GameObject					*newDoor(std::string model);
		static GameObject					*new_Indestructible_block(std::string model);
		static GameObject					*new_Destructible_block(std::string model);
		static GameObject					*new_Ground_block(std::string model);
		static GameObject					*new_Environement_block(std::string model);
		static GameObject					*newPlayer(int Id);
		static GameObject					*newBomb(CharacterControllerScript *playerController);
		static GameObject					*newExplosion(float x, float z, long timer);
		static GameObject					*newBackground(void);
		static GameObject					*newSkybox(void);
		static GameObject 					*newGoomba(int level);
		static GameObject					*newPowerUp(float x, float z);

		Factory( void );
		Factory( Factory const & src );
		virtual ~Factory( void );

		Factory &							operator=( Factory const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Factory const & i);
};

#endif
