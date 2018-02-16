#include "Bomberman.hpp"

// STATIC ########################################################

GameObject							*Factory::newBlock(std::string model)
{
	GameObject	*obj = new GameObject();

	obj->tag = model;
	obj->AddComponent<Model>(Model::model[model]);
	return (obj);
}

GameObject							*Factory::newPlayer(void)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Player";
	obj->AddComponent<Model>(Model::model["bomberman"]);
	obj->AddComponent<BoxCollider>(new BoxCollider(glm::vec3(0,0,0), glm::vec3(0.4f,0.25f,0.4f)));
	obj->AddComponent<Script>(new CharacterControllerScript(1));
	return (obj);
}
GameObject							*Factory::newPlayer2(void)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Player2";
	obj->AddComponent<Model>(Model::model["bomberman2"]);
	obj->AddComponent<BoxCollider>(new BoxCollider(glm::vec3(0,0,0), glm::vec3(0.4f,0.25f,0.4f)));
	obj->AddComponent<Script>(new CharacterControllerScript(2));
	return (obj);
}

GameObject							*Factory::newBomb(void)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Bomb";
	obj->AddComponent<Model>(Model::model["bomb"]);
	obj->AddComponent<Script>(new BombControllerScript());
	return (obj);
}

GameObject							*Factory::newExplosion(float x, float z, long timer)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Explosion";
	obj->transform.position = glm::vec3(x, 0, z);
	obj->transform.scale = glm::vec3(4.f, 4.f, 4.f);
	obj->AddComponent<Model>(Model::model["flamme_block"]);
	obj->AddComponent<Script>(new ExplosionControllerScript(timer));
	return (obj);
}

// ###############################################################

// CANONICAL #####################################################

Factory::Factory ( void )
{
	return ;
}

Factory::Factory ( Factory const & src )
{
	*this = src;
	return ;
}

Factory &				Factory::operator=( Factory const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Factory::~Factory ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Factory const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
