#include "Bomberman.hpp"

// STATIC ########################################################

std::vector<BombControllerScript*> BombControllerScript::List = std::vector<BombControllerScript*>();

// ###############################################################

// CANONICAL #####################################################

BombControllerScript::BombControllerScript ( CharacterControllerScript *playerController )
{
	BombControllerScript::List.push_back(this);
	this->startTime = TimeUtils::getCurrentSystemMillis();
	this->anim_time = TimeUtils::getCurrentSystemMillis();
	this->sens = false;
	this->max_scale = 2.f;
	this->min_scale = 1.f;

	this->power = playerController->getPower();
	this->playerController = playerController;
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
	BombControllerScript::List.erase(std::remove(BombControllerScript::List.begin(), BombControllerScript::List.end(), this));
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
	if (TimeUtils::getCurrentSystemMillis() > this->startTime + BOMB_TIME) {
		this->explode();
		return ;
	}
	if (TimeUtils::getCurrentSystemMillis() < this->anim_time + 40L)
		return ;
	if (this->sens == false)
	{
		this->gameObject->transform.scale.x -= 0.1f;
		this->gameObject->transform.scale.y -= 0.1f;
		this->gameObject->transform.scale.z -= 0.1f;

		this->gameObject->transform.position.y += 0.01f;
		if (this->gameObject->transform.scale.x <= this->min_scale)
			this->sens = true;
	} else {
		this->gameObject->transform.scale.x += 0.1f;
		this->gameObject->transform.scale.y += 0.1f;
		this->gameObject->transform.scale.z += 0.1f;

		this->gameObject->transform.position.y -= 0.01f;
		if (this->gameObject->transform.scale.x >= this->max_scale)
			this->sens = false;
	}
	this->anim_time = TimeUtils::getCurrentSystemMillis();
}

void								BombControllerScript::OnPreRender(void)
{

	float timer = 1.0f - ((this->startTime + BOMB_TIME - TimeUtils::getCurrentSystemMillis())/(float)BOMB_TIME);

	Model *bombObjectModel = this->gameObject->GetComponent<Model>();
	glUseProgram(bombObjectModel->shader);
	bombObjectModel->shaderBind = true;

	glm::vec3 colors = glm::vec3(timer,0.f,0.f);
	glUniform3fv(bombObjectModel->color,1 , &colors[0]);

	//TODO add meche color in shader
}

void								BombControllerScript::OnEndRender(void)
{

}

void								BombControllerScript::explode(void)
{

	Mix_PlayChannel(-1, BombermanClient::instance->bomb, 0);

	int x = this->gameObject->transform.position.x / 2;
	int z = this->gameObject->transform.position.z / 2;
	this->playerController->BombExplode();
	Case *c = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(x, z);
	if (c == NULL)
		return ;
	c->obstacle = NULL;
	c->walkable = true;
	int puissance = this->power;
	//z+
	for (int i = 1; i < (puissance + 1); i++) {
		Case *b = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(x, z + i);
		if (b == NULL)
			break ;
		BombermanClient::instance->current_scene->add(Factory::newExplosion(x, (z + i), i));
		if (b->obstacle != NULL)
			if (b->obstacle->tag == "ground1" || b->obstacle->tag == "ice_block")
				break;
	}
	//z-
	for (int i = 1; i < (puissance + 1); i++) {
		Case *b = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(x, z - i);
		if (b == NULL)
			break ;
		BombermanClient::instance->current_scene->add(Factory::newExplosion(x, (z - i), i));
		if (b->obstacle != NULL)
			if (b->obstacle->tag == "ground1" || b->obstacle->tag == "ice_block")
				break;
	}
	//x+
	for (int i = 1; i < (puissance + 1); i++) {
		Case *b = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(x + i, z);
		if (b == NULL)
			break ;
		BombermanClient::instance->current_scene->add(Factory::newExplosion((x + i), z, i));
		if (b->obstacle != NULL)
			if (b->obstacle->tag == "ground1" || b->obstacle->tag == "ice_block")
				break;
	}
	//x-
	for (int i = 1; i < (puissance + 1); i++) {
		Case *b = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(x - i, z);
		if (b == NULL)
			break ;
		BombermanClient::instance->current_scene->add(Factory::newExplosion((x - i), z, i));
		if (b->obstacle != NULL)
			if (b->obstacle->tag == "ground1" || b->obstacle->tag == "ice_block")
				break;
	}
	BombermanClient::instance->current_scene->remove(this->gameObject);
	delete this->gameObject;
	delete this;
}

// ###############################################################
