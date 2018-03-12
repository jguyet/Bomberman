#include "managers/DoorManager.hpp"

DoorManager::DoorManager ()
{
}

DoorManager::DoorManager ( DoorManager const & src )
{
	*this = src;
}

DoorManager &				DoorManager::operator=( DoorManager const & rhs )
{
	return (*this);
}

DoorManager::~DoorManager ()
{

}

std::ostream &				operator<<(std::ostream & o, DoorManager const & i)
{
	return (o);
}

void DoorManager::setRandomDoor(GameScene *scene)
{
	std::vector<Case*>	possiblesCases = scene->mapManager->getAllDestructibleCases();
	Random				random;
	int					r = random.getRandom(0, possiblesCases.size() - 1);

	if (possiblesCases.size() > 0 && r >= 0)
	{
		Case *selectedCase = possiblesCases[r];
		selectedCase->obstacle->transform.scale = glm::vec3(1.8f, 1.8f, 1.8f);
		selectedCase->walkable = false;

		selectedCase->door = true;
	}
}
