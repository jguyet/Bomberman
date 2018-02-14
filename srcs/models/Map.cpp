#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Map::Map ( void )
{
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

	// GetMaps::get_all_maps();
	///// GRASS
	// for (int z = 0; z < 19; z++) {
	// 	for (int x = 0; x < 13; x++) {
	// 		GameObject *block = Factory::newBlock("grass");
	// 		block->transform.position = glm::vec3(x * 2,2,z * 2);
	// 		this->cases[std::make_pair(x, z)]->ground = block;
	// 		this->cases[std::make_pair(x, z)]->walkable = true;
	// 	}
	// }

	///// WALS
	// for (int z = 0; z < 19; z++) {
	// 	for (int x = 0; x < 13;) {
	// 		GameObject *block = Factory::newBlock("brick");
	// 		block->transform.position = glm::vec3(x * 2,0,z * 2);
	// 		this->cases[std::make_pair(x, z)]->obstacle = block;
	// 		this->cases[std::make_pair(x, z)]->walkable = false;
	// 		if (z == 0 || z == 18 || x == 12) {
	// 			i++;
	// 			x++;
	// 		}
	// 		else {
	// 			x = 12;
	// 		}
	// 	}
	// }

	///// Obstacles
	// for (int z = 0; z < 19; z++) {
	// 	for (int x = 0; x < 13;x++) {
	// 		if (z == 0 || z == 18 || x == 0 || x == 12 || z % 2 || x % 2) {
	// 			continue ;
	// 		}
	// 		GameObject *block = Factory::newBlock("brick");
	// 		block->transform.position = glm::vec3(x * 2,0.5f,z * 2);
	// 		block->transform.scale.y = 0.5f;
	// 		this->cases[std::make_pair(x, z)]->obstacle = block;
	// 		this->cases[std::make_pair(x, z)]->walkable = false;
	// 	}
	// }
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

void						Map::render(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix)
{
	for (std::map<std::pair<float, float>, Case*>::iterator it = this->cases.begin(); it != this->cases.end(); ++it)
	{
		Case *c = it->second;
		if (c->obstacle != NULL)
			c->obstacle->ProcessRenderingComponents(projectionMatrix, viewMatrix);
		if (c->ground != NULL)
			c->ground->ProcessRenderingComponents(projectionMatrix, viewMatrix);
	}
}

Case						*Map::getCase(int x, int z)
{
	if (this->cases.count(std::make_pair(x, z)) == 0)
		return (NULL);
	return (this->cases[std::make_pair(x, z)]);
}

// ###############################################################
