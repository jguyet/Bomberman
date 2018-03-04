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
	std::vector<Case*>	possiblesCases = scene->mapManager->getAllBlockingCase(scene->map);
	Random				random;
	if (possiblesCases.size() > 0)
	{
		Case *selectedCase = possiblesCases[random.getRandom(0, possiblesCases.size())];
		selectedCase->obstacle->transform.scale = glm::vec3(10.5f, 10.5f, 10.5f);
		
		selectedCase->door = Factory::newBlock("door");
		selectedCase->door->transform.scale = glm::vec3(0.01f, 0.01f, 0.01f);
		selectedCase->door->transform.rotation = glm::vec3(0,0,0);
		selectedCase->door->transform.position = selectedCase->obstacle->transform.position;
	}
}
