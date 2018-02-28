#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

ExplosionControllerScript::ExplosionControllerScript ( long timer )
{
	this->timer = timer;
	return ;
}

ExplosionControllerScript::ExplosionControllerScript ( ExplosionControllerScript const & src )
{
	*this = src;
	return ;
}

ExplosionControllerScript &				ExplosionControllerScript::operator=( ExplosionControllerScript const & rhs )
{
	return (*this);
}

ExplosionControllerScript::~ExplosionControllerScript ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, ExplosionControllerScript const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						ExplosionControllerScript::Start(void)
{
	this->gameObject->transform.scale = glm::vec3(0.f, 0.f, 0.f);
	this->startTime = TimeUtils::getCurrentSystemMillis();
	this->timerExplode = this->startTime;
}

void						ExplosionControllerScript::Update(void)
{
	if (TimeUtils::getCurrentSystemMillis() > (this->startTime + (this->timer * 30L))) {
		if (this->timerExplode < TimeUtils::getCurrentSystemMillis() && this->gameObject->transform.scale.x < 4.f) {
			this->gameObject->transform.scale+=0.15f;
			this->timerExplode = TimeUtils::getCurrentSystemMillis() + 1L;
		}
	}
	if (TimeUtils::getCurrentSystemMillis() > (this->startTime + (this->timer * 50L) + 200L)) {

		float x = this->gameObject->transform.position.x / 2;
		float z = this->gameObject->transform.position.z / 2;
		Case *b = dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->map->getCase(x, z);

		if (b->obstacle != NULL) {
			if (b->obstacle->tag == "Bomb") {
				dynamic_cast<BombControllerScript*>(b->obstacle->GetComponent<Script>())->startTime = 0;
			} else if (b->obstacle->tag != "ground1") {
				if (b->obstacle->tag == "ice_block")
				{
					if (BombermanClient::getInstance()->sock->state == false) {
						BombermanClient::getInstance()->current_scene->add(Factory::newPowerUp(x, z));
					} else {
						BombermanClient::getInstance()->sock->newBonus(x, z);
					}
				}
				BombermanClient::getInstance()->current_scene->remove(b->obstacle);
				delete b->obstacle;
				b->obstacle = NULL;
				b->walkable = true;
			}
		}

		BombermanClient::getInstance()->current_scene->remove(this->gameObject);
		delete this->gameObject;
		delete this;
	}
}

// ###############################################################
