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
		GameScene *scene = BombermanClient::getInstance()->getCurrentScene<GameScene>();
		Case *b = scene->map->getCase(x, z);

		if (b->obstacle != NULL) {
			if (b->obstacle->tag == "Bomb") {
				dynamic_cast<BombControllerScript*>(b->obstacle->GetComponent<Script>())->startTime = 0;
			} else if (b->obstacle->tag == "destructible_block")
			{
				if (BombermanClient::getInstance()->sock) {
					if (BombermanClient::getInstance()->sock->state == false) {
						scene->add(Factory::newPowerUp(x, z));
					} else {
						BombermanClient::getInstance()->sock->newBonus(x, z);
					}
				}
				if (b->door != NULL)
					scene->add(b->door);
				b->obstacle->toDelete = true;
				b->obstacle = NULL;
				b->walkable = true;
			}
		}
		this->gameObject->toDelete = true;
	}
}

// ###############################################################
