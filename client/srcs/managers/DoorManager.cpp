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
	if (possiblesCases.size() > 0)
	{
		Case *selectedCase = possiblesCases[random.getRandom(0, possiblesCases.size() - 1)];
		selectedCase->obstacle->transform.scale = glm::vec3(1.f, 1.f, 1.f);
		selectedCase->walkable = false;

		selectedCase->door = Factory::newDoor("door");
		selectedCase->door->transform.position = selectedCase->obstacle->transform.position;
		selectedCase->door->transform.position.y -= 1.5;
	}
}
