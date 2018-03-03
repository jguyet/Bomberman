#include "managers/SaveManager.hpp"
#include <fstream>

SaveManager::SaveManager ()
{
	this->saveObject = this->loadSave();
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
	if (this->saveObject)
		delete this->saveObject;
}

std::ostream &				operator<<(std::ostream & o, SaveManager const & i)
{
	return (o);
}

void SaveManager::save(std::string map_name)
{
	std::ofstream outfile ("/tmp/.save.bomberman", std::ofstream::binary);
	if (outfile.is_open()) {
		SaveObject object;
		memset((char*)&object.map_name, 0, (MAP_NAME_LEN - 1));
		snprintf((char*)&object.map_name, (MAP_NAME_LEN - 1), "%s", map_name.c_str());
		outfile.write((char*)&object, sizeof(SaveObject));

		printf("Save loaded, currently on map: %s\n", object.map_name);
	} else {
		std::cerr << "Can't open save file to save current progression !" << std::endl;
	}
}

template<typename T>
std::istream & binary_read(std::istream& stream, T& value){
    return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

SaveObject *SaveManager::loadSave()
{
	std::ifstream	infile("/tmp/.save.bomberman", std::ios::binary);
	if (infile.is_open()) {
		SaveObject *object = new SaveObject();
		infile.read(reinterpret_cast<char*>(object), sizeof(SaveObject));
		binary_read(infile, object);

		printf("Save loaded, currently on map: %s\n", object->map_name);
		return object;
	}
	return NULL;
}
