#include "Bomberman.hpp"

// STATIC ########################################################

GameObject							*Factory::newBlock(std::string model)
{
	GameObject	*obj = new GameObject();

	obj->tag = model;
	obj->AddComponent<Model>(Model::model[model]);
	return (obj);
}

GameObject							*Factory::newPlayer(int id)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Donkey Kong";

	//ANIMATOR
	Animator *animator = new Animator();
	animator->newAnimation("idle", 1000L, 2, Model::model["bomberman"]);
	animator->newAnimation("walk", 100L, 4, Model::model["walk_0"], Model::model["walk_1"], Model::model["walk_2"], Model::model["walk_3"]);
	animator->handleAnimation("idle");
	obj->AddComponent<Animator>(animator);
	obj->AddComponent<BoxCollider>(new BoxCollider(glm::vec3(0,0,0), glm::vec3(0.4f,0.25f,0.4f)));
	obj->AddComponent<Script>(new CharacterControllerScript(id));
	return (obj);
}

GameObject							*Factory::newBomb(CharacterControllerScript *playerController)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Bomb";

	obj->AddComponent<Model>(Model::model["bomb"]);
	obj->AddComponent<Script>(new BombControllerScript(playerController));
	return (obj);
}

GameObject							*Factory::newExplosion(float x, float z, long timer)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Explosion";
	obj->transform.position = glm::vec3(x*2, 0, z*2);
	obj->transform.scale = glm::vec3(0.f, 0.f, 0.f);
	obj->AddComponent<Model>(Model::model["flamme_block"]);
	obj->AddComponent<Script>(new ExplosionControllerScript(timer-1));
	return (obj);
}

GameObject 							*Factory::newBackground(void)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Background";
	obj->transform.position = glm::vec3(25.f, 2, 20.f);
	obj->transform.scale = glm::vec3(40.f, 1.f, 40.f);
	obj->AddComponent<Model>(Model::model["brick"]);
	return (obj);
}

GameObject 							*Factory::newSkybox(void)
{
	GameObject	*obj = new GameObject();

	obj->tag = "Skybox";
	obj->transform.position = glm::vec3(0, 1000, 0);
	obj->transform.scale = glm::vec3(10000.f, -10000.f, 10000.f);
	obj->AddComponent<Model>(Model::model["skybox"]);
	return (obj);
}

GameObject							*Factory::newPowerUp(float x, float z)
{
	GameObject	*obj = new GameObject();
	obj->transform.position = glm::vec3(x*2, 0, z*2);
	obj->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);

	int nb = rand() % 100 + 1;

	if (nb < 10) {
			obj->tag = "bonus-power-up";
			obj->AddComponent<Model>(Model::model["bonus-power-up"]);
	} else if (nb < 20) {
			obj->tag = "bonus-speed-up";
			obj->AddComponent<Model>(Model::model["bonus-speed-up"]);
	}
	else if (nb < 30){
			obj->tag = "bonus-bomb-up";
			obj->AddComponent<Model>(Model::model["bonus-bomb-up"]);
	}
	else {
			delete obj;
			obj = NULL;
	}

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
