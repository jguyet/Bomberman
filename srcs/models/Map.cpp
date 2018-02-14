#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Map::Map ( Scene *scene )
{
	this->scene = scene;
	//Faire un chargement dans un fichier (si tes pas content !!!!)
	int i = 0;
	// GetMaps *test = new GetMaps();
	static GetMaps test;
	std::cout << "-------|---------|-----------" << std::endl;
	test.get_all_maps();
	std::cout << "-------|---------|-----------" << std::endl;

	for (int z = 0; z < 19; z++) {
		for (int x = 0; x < 13; x++) {
			this->cases[std::make_pair(x, z)] = new Case();
		}
	}

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
	for (std::map<std::pair<float, float>, Case*>::iterator it = this->cases.begin(); it != this->cases.end(); ++it)
	{
		Case *c = it->second;
		if (c->obstacle != NULL) {
			this->scene->add(c->obstacle);
		}
		if (c->ground != NULL) {
			this->scene->add(c->ground);
		}
	}
}

Case						*Map::getCase(int x, int z)
{
	if (this->cases.count(std::make_pair(x, z)) == 0)
		return (NULL);
	return (this->cases[std::make_pair(x, z)]);
}

// ###############################################################
