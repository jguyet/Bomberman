#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

BombControllerScript::BombControllerScript ( void )
{
	this->startTime = TimeUtils::getCurrentSystemMillis();
	return ;
}

BombControllerScript::BombControllerScript ( BombControllerScript const & src )
{
	*this = src;
	return ;
}

BombControllerScript &				BombControllerScript::operator=( BombControllerScript const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

BombControllerScript::~BombControllerScript ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, BombControllerScript const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void								BombControllerScript::Update(void)
{
	if (TimeUtils::getCurrentSystemMillis() > this->startTime + 5000L) {
		this->explode();
	}
}

void								BombControllerScript::explode(void)
{
	int x = this->gameObject->transform.position.x / 2;
	int z = this->gameObject->transform.position.z / 2;
	Case *c = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(x, z);
	if (c == NULL)
		return ;
	c->obstacle = NULL;
	int puissance = 4;
	for (int i = 1; i < (puissance + 1); i++) {

		BombermanClient::instance->current_scene->add(Factory::newExplosion(x*2, (z + i)*2));
		BombermanClient::instance->current_scene->add(Factory::newExplosion(x*2, (z - i)*2));
		BombermanClient::instance->current_scene->add(Factory::newExplosion((x + i)*2, z*2));
		BombermanClient::instance->current_scene->add(Factory::newExplosion((x - i)*2, z*2));
		
		Case *b = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(x, z + i);

		if (b != NULL && b->obstacle != NULL && b->obstacle->tag == "brick") {
			BombermanClient::instance->current_scene->remove(b->obstacle);
			delete b->obstacle;
			b->obstacle = NULL;
			b->walkable = true;
		}

		b = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(x, z - i);
		if (b != NULL && b->obstacle != NULL && b->obstacle->tag == "brick") {
			BombermanClient::instance->current_scene->remove(b->obstacle);
			delete b->obstacle;
			b->obstacle = NULL;
			b->walkable = true;
		}

		b = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(x + i, z);
		if (b != NULL && b->obstacle != NULL && b->obstacle->tag == "brick") {
			BombermanClient::instance->current_scene->remove(b->obstacle);
			delete b->obstacle;
			b->obstacle = NULL;
			b->walkable = true;
		}

		b = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(x - i, z);
		if (b != NULL && b->obstacle != NULL && b->obstacle->tag == "brick") {
			BombermanClient::instance->current_scene->remove(b->obstacle);
			delete b->obstacle;
			b->obstacle = NULL;
			b->walkable = true;
		}
	}
	BombermanClient::instance->current_scene->remove(this->gameObject);
	delete this->gameObject;
	delete this;
}

// ###############################################################
