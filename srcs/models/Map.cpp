#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Map::Map ( void )
{

	//Faire un chargement dans un fichier (si tes pas content !!!!)
	int i = 0;
	for (int z = 0; z < 19; z++) {
		for (int x = 0; x < 13; x++) {

			Block *block = new Block(Model::model["grass"]);

			block->gameObject.transform.position = glm::vec3(x,0.5f,z);
			block->gameObject.transform.scale = glm::vec3(1,1,1);

			Case *c = new Case();
			c->obstacle = NULL;
			c->ground = block;

			this->cases[i++] = c;
		}
	}
	i = 0;
	for (int z = 0; z < 19; z++) {
		for (int x = 0; x < 13;) {

			Block *block = new Block(Model::model["brick"]);

			block->gameObject.transform.position = glm::vec3(x,-0.5f,z);
			block->gameObject.transform.scale = glm::vec3(1,1,1);

			this->cases[i]->obstacle = block;

			if (z == 0 || z == 18 || x == 12) {
				i++;
				x++;
			}
			else {
				x = 12;
				i += 12;
			}
		}
	}
	i = 0;
	for (int z = 0; z < 19; z++) {
		for (int x = 0; x < 13;x++) {
			if (z == 0 || z == 18 || x == 0 || x == 13 || z % 2 || x % 2) {
				i++;
				continue ;
			}
			Block *block = new Block(Model::model["brick"]);
			block->gameObject.transform.position = glm::vec3(x,-0.5f,z);
			block->gameObject.transform.scale = glm::vec3(1,1,1);

			this->cases[i]->obstacle = block;
			i++;
		}
	}
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
	for (std::map<unsigned int, Case*>::iterator it = this->cases.begin(); it != this->cases.end(); ++it)
	{
		Case *c = it->second;
		if (c->obstacle != NULL)
			c->obstacle->gameObject.ProcessRenderingComponents(projectionMatrix, viewMatrix);
		if (c->ground != NULL)
			c->ground->gameObject.ProcessRenderingComponents(projectionMatrix, viewMatrix);
	}
}

// ###############################################################
