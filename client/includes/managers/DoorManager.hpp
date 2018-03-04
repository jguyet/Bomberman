#ifndef DOORMANAGER_HPP
# define DOORMANAGER_HPP

#include "Bomberman.hpp"
#include "models/Map.hpp"
#include "scenes/GameScene.hpp"
#include "utils/Random.hpp"

class DoorManager
{
	public:
		DoorManager();
		DoorManager( DoorManager const & src );
		virtual ~DoorManager();

		static void 							setRandomDoor(GameScene*);

		DoorManager &							operator=( DoorManager const & rhs );
		friend std::ostream &					operator<<(std::ostream & o, DoorManager const & i);
};

#endif
