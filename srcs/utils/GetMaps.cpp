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

void	GetMaps::get_all_maps(void)
{
	if (this->get_dir_maps() == -1)
		return ;
	// int n_count = std::distance(words_begin2, words_end2);

	std::cout << "-------|start|-----------" << std::endl;

	// std::string st = "            43          people,          2     confronted 45 a problem, think ";
	for (auto & element : this->maps_names)
		this->load_map(element);

	std::cout << "-------|start2|-----------" << std::endl;

	return ;
}

void	GetMaps::load_map(std::string name)
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

	for (auto const& value: segvec)
	{
		std::cout << "|" << value << "|" << std::endl;
		std::cout << "Found " << std::distance(std::sregex_iterator(value.begin(), value.end(), any_regex), std::sregex_iterator()) << " words\n";
		// int c_count = std::distance(words_begin, words_end);
		std::cout << "Found " << std::distance(std::sregex_iterator(value.begin(), value.end(), number_regex),std::sregex_iterator()) << " words\n";
		// int n_count = std::distance(words_begin, words_end);
	}
	filestr.close();
}

// ###############################################################

// PRIVATE METHOD #################################################

int		GetMaps::get_dir_maps(void)
{
	DIR *dir;
	struct dirent *ent;

	struct stat info;

	if (stat("maps/", &info ) != 0)
	{
		std::cout << "cannot access maps/" << std::endl;
		return (-1);
	}
	else if ( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows
	{
		if ((dir = opendir("maps/")) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				if (strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0)
				{
					// std::cout << ent->d_name << std::endl;
					this->maps_names.push_back(ent->d_name);
					std::cout << this->maps_names.front() << std::endl;
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
