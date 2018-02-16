#include "managers/MapManager.hpp"

MapManager::MapManager (Scene *scene) : scene(scene)
{
	this->loadMaps();
}

MapManager::MapManager ( MapManager const & src )
{
	*this = src;
}

MapManager &				MapManager::operator=( MapManager const & rhs )
{
	return (*this);
}

void	MapManager::loadMaps()
{
	this->readMaps();
	for (auto &elem : this->maps)
	{
		Map *current = elem.second;
		this->parseMaps(current->getName(), current->content);
	}
}

Map		*MapManager::getMap(std::string name)
{
	return this->maps[name];
}

void	MapManager::readMaps()
{
	DIR *dir;
	struct dirent *ent;
	struct stat info;

	if (stat("maps/", &info ) != 0) {
		std::cout << "Cannot access maps" << std::endl;
		return ;
	}
	else if (info.st_mode & S_IFDIR)
	{
		if ((dir = opendir("maps/")) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				if (strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0) {
					this->maps.insert(std::pair<std::string, Map*>(ent->d_name, new Map(ent->d_name)));
				}
			}
			closedir(dir);
			return ;
		}
	}
}

/*
**	Please lord understand that this is not my code
*/

void	MapManager::parseMaps(std::string name, std::map<std::pair<int, int>, Case> &map)
{
	std::fstream filestr;
	std::string segment;
	std::vector<std::string> segvec;
	std::regex any_regex("(\\S+)");
	std::regex number_regex("(\\d+)");
	std::string path = "maps/";

	path.append(name);
	filestr.open(path);

	auto ss = std::ostringstream{};
	ss << filestr.rdbuf();
	std::stringstream s(ss.str());

	while (std::getline(s, segment, '\n'))
		segvec.push_back(segment);

	int y = 0;
	for (auto const& value: segvec)
	{
		if (std::distance(std::sregex_iterator(value.begin(), value.end(), any_regex), std::sregex_iterator())
		!= std::distance(std::sregex_iterator(value.begin(), value.end(), number_regex),std::sregex_iterator()))
		{
			std::cout << "ERROR to pars map " << path << " at line " << value << std::endl;
			map.clear();
			filestr.close();
			return ;
		}
		else {
			auto words_begin = std::sregex_iterator(value.begin(), value.end(), number_regex);
			auto words_end = std::sregex_iterator();
			int x = 0;

			for (std::sregex_iterator i = words_begin; i != words_end; ++i)
			{
				try {
					std::string::size_type sz;
					std::smatch match = *i;
					int i_dec = std::stoi (match.str() ,&sz);

					if (this->setBlock(map, x, y, i_dec))
					{
						std::cout << "ERROR to pars map " << path << " at line " << value << std::endl;
						map.clear();
						filestr.close();
						return ;
					}
				} catch (std::exception& e) {
					std::cout << "ERROR to pars map " << path << " at line " << value << " | " << e.what() << std::endl;
					map.clear();
					filestr.close();
					return ;
				}
				x++;
			}
			y++;
		}
	}
	filestr.close();
}

/*
**	This is not on me.
*/

<<<<<<< HEAD:client/srcs/utils/GetMaps.cpp
// PRIVATE METHOD #################################################

int		GetMaps::set_block(std::map<std::pair<int, int>, Case> &map, int y, int x, int value)
=======
int		MapManager::setBlock(std::map<std::pair<int, int>, Case> &map, int x, int y, int value)
>>>>>>> b10dccf259cd10532bb2141995577db512f31633:client/srcs/managers/MapManager.cpp
{
	Case cube;
	GameObject *block;
	static std::map<int, std::string> links =
	{
		std::make_pair(0, "ground1"), std::make_pair(1, "ice_block"), std::make_pair(2, "ground1")
	};

	block = Factory::newBlock(links[0]);
	block->transform.position = glm::vec3(x * 2, GROUND, y * 2);
	block->transform.scale = glm::vec3(3.7f, 3.5f, 3.7f);
	cube.ground = block;
	cube.obstacle = NULL;
	cube.walkable = true;

	cube.position = glm::vec3(x * 2, 0, y * 2);

	if (value != 0)
	{
		if (links.count(value) != 0)
			block = Factory::newBlock(links[value]);
		else
			return (1);

		block->transform.position = glm::vec3(x * 2, WALL, y * 2);
		block->transform.scale = glm::vec3(3.5f, 3.5f, 3.5f);
		cube.obstacle = block;
		cube.walkable = false;
	}
	map[std::make_pair(x, y)] = cube;
	return (0);
}

void						MapManager::buildObjects(Map *selected)
{
	for (auto & elem : selected->content)
	{
		if (elem.second.obstacle != NULL) {
			this->scene->add(elem.second.obstacle);
		}
		if (elem.second.ground != NULL) {
			this->scene->add(elem.second.ground);
		}
	}
}

MapManager::~MapManager ()
{
	// for (auto &elem : this->maps)
	// {
	// 	delete elem.second;
	// }
}

std::ostream &				operator<<(std::ostream & o, MapManager const & i)
{

	return (o);
}
