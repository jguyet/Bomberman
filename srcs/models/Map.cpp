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
	this->current_map = "";
	this->current_map = "map_01";
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
	if (this->maps.count(this->current_map) != 0)
	{
		for (auto & elem : this->maps[this->current_map])
		{
			if (elem.second.obstacle != NULL) {
				this->scene->add(elem.second.obstacle);
			}
			if (elem.second.ground != NULL) {
				this->scene->add(elem.second.ground);
			}
		}
	}
}

Case						&Map::getCase(int x, int z)
{
	if (this->maps.count(this->current_map) != 0)
	{
		// if (this->maps[this->current_map].count(std::make_pair(x, z)) == 0)
		// 	return ;
	}
	return (this->maps[this->current_map][std::make_pair(x, z)]);
}

// ###############################################################
