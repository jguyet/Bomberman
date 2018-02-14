#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Map::Map ( Scene *scene )
{
	this->scene = scene;
	//Faire un chargement dans un fichier (si tes pas content !!!!)
	int i = 0;
	static GetMaps gmap;

	std::cout << "-------|---------|-----------" << std::endl;
	gmap.get_all_maps(this->maps);
	std::cout << "-------|---------|-----------" << std::endl;

	this->build();
	return ;
}

Map::Map ( Map const & src )
{
	*this = src;
	return ;
}

Map &				Map::operator=( Map const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Map::~Map ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Map const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Map::build(void)
{
	if (this->maps.count("map_01") != 0)
	{
		std::cout  << "test >>>>>>>>>>>>>>>>> " << std::endl;
		for (auto & elem : this->maps["map_01"])
		{
			std::cout  << "-------------------- " << std::endl;
			if (elem.second.obstacle != NULL) {
				this->scene->add(elem.second.obstacle);
			}
			std::cout  << "-------------------- 1" << std::endl;
			if (elem.second.ground != NULL) {
				this->scene->add(elem.second.ground);
			}
			std::cout  << "-------------------- 2" << std::endl;
		}
	}
	std::cout  << "fin" << std::endl;
}

// Case						*Map::getCase(int x, int z)
// {
// 	if (this->cases.count(std::make_pair(x, z)) == 0)
// 		return (NULL);
// 	return (this->cases[std::make_pair(x, z)]);
// }

// ###############################################################
