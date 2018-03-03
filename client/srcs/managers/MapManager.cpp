#include "managers/MapManager.hpp"

MapManager::MapManager (Scene *scene) : scene(scene)
{
	this->loadMaps();
}

MapManager::MapManager (void)
{
	return;
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
	return (this->maps.count(name) > 0) ? this->maps[name] : NULL;
}

Case	*MapManager::getRandomWalkableCase(Map *from)
{
	std::vector<Case*> walkables;
	Random randomGen;
	for (auto & elem : from->content)
	{
		if (elem.second.ground && !elem.second.obstacle) {
			walkables.push_back(&elem.second);
		}
	}
	return (walkables.size() > 0) ? walkables[randomGen.getRandom(0, walkables.size())] : NULL;
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
			std::cout << "ERROR to parse map " << path << " at line " << value << std::endl;
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
					this->setBlock(map, x, y, i_dec);
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

// PRIVATE METHOD #################################################

int		MapManager::setBlock(std::map<std::pair<int, int>, Case> &map, int x, int y, int value)
{
	Case			cube;
	GameObject		*block;

	static std::map<int, std::string> links =
	{
		std::make_pair((int)BlockType::TYPE_BRICK, "brick"),
		std::make_pair((int)BlockType::TYPE_ICE_BLOCK, "ice_block"),
		std::make_pair((int)BlockType::TYPE_GROUND, "ground1"),
		std::make_pair((int)BlockType::TYPE_GOOMBA, "goomba")
	};

	block = Factory::newBlock(links[0]);
	block->transform.position = glm::vec3(x * 2, GROUND, y * 2);
	block->transform.scale = glm::vec3(1.f, 1.f, 1.f);
	cube.ground = block;
	cube.obstacle = NULL;
	cube.door = NULL;
	cube.walkable = true;
	cube.position = glm::vec3(x * 2, 0, y * 2);

	if (value != 0 && links.count(value) != 0)
	{
		if (value != (int)BlockType::TYPE_GOOMBA) {
			block = Factory::newBlock(links[value]);
			block->transform.position = glm::vec3(x * 2, WALL, y * 2);
			block->transform.scale = glm::vec3(3.5f, 3.5f, 3.5f);
			cube.obstacle = block;
			cube.walkable = false;
		}
		else if (BombermanClient::getInstance()->sock->state == false)
		{
			block = Factory::newGoomba();
			block->transform.position = glm::vec3(x * 2, 0, y * 2);
			cube.obstacle = block;
		}
	}
	map[std::make_pair(x, y)] = cube;
	return (0);
}

void						MapManager::buildObjects(Map *selected)
{

	for (auto & elem : selected->content)
	{
		if (elem.second.obstacle != NULL)
		{
			if (elem.second.obstacle->tag == "Goomba")
			{
				GameObject *player = Factory::newGoomba();
				// this->all_player.push_back(player);
				// this->players.push_back(player);
				player->transform.position = glm::vec3(elem.second.obstacle->transform.position.x, 0, elem.second.obstacle->transform.position.z);
				player->transform.scale = glm::vec3(0.05f,0.05f,0.05f);
				this->scene->add(player); //add on scene
				elem.second.obstacle = NULL;
			}
			else
				this->scene->add(elem.second.obstacle);
		}
	}
	this->scene->add(Factory::newBackground());
	this->scene->add(Factory::newSkybox());
}

MapManager::~MapManager ()
{
	for (auto &elem : this->maps)
	{
		Map *current = elem.second;

		delete current;
	}
	this->maps.clear();
}

std::ostream &				operator<<(std::ostream & o, MapManager const & i)
{

	return (o);
}
