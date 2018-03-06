#include "managers/SaveManager.hpp"
#include <fstream>

SaveManager::SaveManager ()
{
	const char		*homedir;

	if ((homedir = getenv("HOME")) == NULL) {
    	homedir = getpwuid(getuid())->pw_dir;
	}
	if (homedir != NULL) {
		this->save_file = std::string(homedir) + "/.save.bomberman";
	} else {
		this->save_file = "/tmp/.save.bomberman";
	}
	std::cout << "Save file is " << this->save_file << std::endl;
	this->saveObject = NULL;
	this->loadSave();
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
	int mapLevel = this->mapToLevel(map_name);
	if (mapLevel >= this->getCurrentLevel()) {
		std::ofstream outfile (this->save_file, std::ofstream::binary);
		if (outfile.is_open()) {
			if (!this->saveObject) {
				this->saveObject = new SaveObject();
			}
			memset((char*)&this->saveObject->map_name, 0, (MAP_NAME_LEN - 1));
			snprintf((char*)&this->saveObject->map_name, (MAP_NAME_LEN - 1), "%s", map_name.c_str());
			outfile.write((char*)this->saveObject, sizeof(SaveObject));

			printf("Save loaded, currently on map: %s\n", this->saveObject->map_name);
		} else {
			std::cerr << "Can't open save file to save current progression !" << std::endl;
		}
	}
}

template<typename T>
std::istream & binary_read(std::istream& stream, T& value){
    return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

SaveObject *SaveManager::loadSave()
{
	std::ifstream	infile(this->save_file, std::ios::binary);
	if (infile.is_open()) {
		this->saveObject = new SaveObject();
		infile.read(reinterpret_cast<char*>(this->saveObject), sizeof(SaveObject));
		binary_read(infile, this->saveObject);

		printf("Saved, currently on map: %s\n", this->saveObject->map_name);
		return this->saveObject;
	}
	return NULL;
}

int SaveManager::getCurrentLevel()
{
	int current_level = 1;
	if (this->saveObject) {
		current_level = this->mapToLevel(this->saveObject->map_name);
	}
	return current_level;
}

int SaveManager::mapToLevel(std::string map)
{
	int level = 1;
	if (map == "map_01")
		level = 1;
	else if (map == "map_02")
		level = 2;
	else if (map == "map_03")
		level = 3;
	else if (map == "map_04")
		level = 4;
	return level;
}

void SaveManager::loadNextLevel()
{
	BombermanClient *instance = BombermanClient::getInstance();
	int	next_level = this->mapToLevel(BombermanClient::getInstance()->getCurrentScene<GameScene>()->map->name) + 1;

	if (next_level > 4)
		next_level = 4;
	std::string level_name = "map_0" + std::to_string(next_level);
	BombermanClient::getInstance()->setCurrentScene<GameScene>(new GameScene(level_name));
}
