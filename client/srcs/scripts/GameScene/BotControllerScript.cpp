#include "Bomberman.hpp"

// STATIC ########################################################

std::vector<BotControllerScript*> BotControllerScript::List = std::vector<BotControllerScript*>();

// ###############################################################

// CANONICAL #####################################################

BotControllerScript::BotControllerScript ( void ) : CharacterControllerScript(100)
{
	BotControllerScript::List.push_back(this);

	this->startTime = TimeUtils::getCurrentSystemMillis();
	this->anim_time = TimeUtils::getCurrentSystemMillis();
	this->sens = false;
	this->max_scale = -0.1f;
	this->min_scale = -0.05f;
	this->robot = NULL;
	return ;
}

BotControllerScript::BotControllerScript ( BotControllerScript const & src ) : CharacterControllerScript(100)
{
	*this = src;
	return ;
}

BotControllerScript &				BotControllerScript::operator=( BotControllerScript const & rhs )
{
	return (*this);
}

BotControllerScript::~BotControllerScript ( void )
{
	if (this->robot != NULL) {
		delete this->robot;
	}
	BotControllerScript::List.erase(std::remove(BotControllerScript::List.begin(), BotControllerScript::List.end(), this));
	return ;
}

std::ostream &				operator<<(std::ostream & o, BotControllerScript const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void BotControllerScript::Start(void) {
	this->scene = BombermanClient::getInstance()->getCurrentScene<GameScene>();
	this->robot = new AI(this->gameObject);
}

void								BotControllerScript::Update(void)
{
	this->lastPosition = glm::vec3(this->gameObject->transform.position.x, this->gameObject->transform.position.y, this->gameObject->transform.position.z);

	static std::map<int, P> cmd = {
		std::make_pair(SDL_SCANCODE_Q, &CharacterControllerScript::Attack), std::make_pair(SDL_SCANCODE_UP, &CharacterControllerScript::MUp),
		std::make_pair(SDL_SCANCODE_DOWN, &CharacterControllerScript::MDown), std::make_pair(SDL_SCANCODE_LEFT, &CharacterControllerScript::MLeft),
		std::make_pair(SDL_SCANCODE_RIGHT, &CharacterControllerScript::MRight)
	};

	if (CharacterControllerScript::lastDying != 0)
	{
		if (CharacterControllerScript::startDying == 0) {
			CharacterControllerScript::startDying = TimeUtils::getCurrentSystemMillis();
		}
		if (CharacterControllerScript::lastDying < (TimeUtils::getCurrentSystemMillis() - 20L))
		{
			CharacterControllerScript::lastDying = TimeUtils::getCurrentSystemMillis();
			this->gameObject->transform.position.y -= 1;
			this->gameObject->transform.rotation.x += 10;
			this->gameObject->transform.rotation.z += 10;
		}

		if ((TimeUtils::getCurrentSystemMillis() - CharacterControllerScript::startDying) >= 1000L) {
			this->scene->removePlayer(this->gameObject);
			this->gameObject->toDelete = true;
		}
		return;
	}

	int i = 0;
	i = this->robot->brain();

	if (i != 0)
		(this->*cmd[i])();
	CharacterControllerScript::unlockCharacterDirections();
}

void								BotControllerScript::OnPreRender(void)
{

}

// ###############################################################
