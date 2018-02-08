#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Block::Block ( Model *model )
{
	this->gameObject.AddComponent<Model>(model);
	this->gameObject.transform.scale = glm::vec3(1,1,1);
	return ;
}

Block::Block ( Block const & src )
{
	*this = src;
	return ;
}

Block &				Block::operator=( Block const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Block::~Block ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Block const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Block::render(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix)
{
	this->gameObject.ProcessRenderingComponents(projectionMatrix, viewMatrix);
}

// ###############################################################
