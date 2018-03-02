#include "managers/SaveManager.hpp"

SaveManager::SaveManager (GameScene *scene) : scene(scene)
{

}

SaveManager::SaveManager ( SaveManager const & src )
{
	*this = src;
}

SaveManager &				SaveManager::operator=( SaveManager const & rhs )
{
	return (*this);
}

SaveManager::~SaveManager ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, SaveManager const & i)
{

	return (o);
}
