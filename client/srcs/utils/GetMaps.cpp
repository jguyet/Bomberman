#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

GetMaps::GetMaps ( void )
{
	return ;
}

GetMaps::GetMaps ( GetMaps const & src )
{
	*this = src;
	return ;
}

GetMaps &				GetMaps::operator=( GetMaps const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GetMaps::~GetMaps ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, GetMaps const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void	GetMaps::get_all_maps(std::map<std::string, std::map<std::pair<int, int>, Case>> &maps)
{
	if (this->get_dir_maps(maps) == -1)
		return ;
	for (auto & elem : maps)
	{
		std::cout << "-------|---------|-----------" << std::endl;
		this->load_map(elem.first, elem.second);
		std::cout << "-------|---------|-----------" << std::endl;
	}
	return ;
}

void	GetMaps::load_map(std::string name, std::map<std::pair<int, int>, Case> &map)
{
	std::fstream filestr;
	std::string segment;
	std::vector<std::string> segvec;
	std::regex any_regex("(\\S+)");
	std::regex number_regex("(\\d+)");
	std::string path = "maps/";

	path.append(name);
	filestr.open(path);

	std::cout << "loading : " <<  path << std::endl;

	auto ss = std::ostringstream{};
	ss << filestr.rdbuf();
	std::stringstream s(ss.str());

	while (std::getline(s, segment, '\n'))
		segvec.push_back(segment);

	int y = 0;
	for (auto const& value: segvec)
	{
		// std::cout << "|" << value << "|" << std::endl;
		// std::cout << "Found " << std::distance(std::sregex_iterator(value.begin(), value.end(), any_regex), std::sregex_iterator()) << " words\n";
		// std::cout << "Found " << std::distance(std::sregex_iterator(value.begin(), value.end(), number_regex),std::sregex_iterator()) << " words\n";
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

					if (this->set_block(map, x, y, i_dec))
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

// ###############################################################

// PRIVATE METHOD #################################################

int		GetMaps::set_block(std::map<std::pair<int, int>, Case> &map, int x, int y, int value)
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
		// check if exist
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

int			GetMaps::get_dir_maps(std::map<std::string, std::map<std::pair<int, int>, Case>> &maps)
{
	DIR *dir;
	struct dirent *ent;
	struct stat info;

	if (stat("maps/", &info ) != 0)
	{
		std::cout << "cannot access maps/" << std::endl;
		return (-1);
	}
	else if ( info.st_mode & S_IFDIR )
	{
		if ((dir = opendir("maps/")) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				if (strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0)
				{
					// std::cout << ent->d_name << std::endl;
					std::map<std::pair<int, int>, Case> map;
					maps.insert(std::pair<std::string, std::map<std::pair<int, int>, Case>>(ent->d_name, map));
				}
			}
			closedir(dir);
			return (0);
		}
		else
		{
			std::cout << "open faile of dir maps" << std::endl;
			return (-1);
		}
	}
	else
	{
		std::cout << "maps is not a directory" << std::endl;
		return (-1);
	}
}

// ###############################################################
