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
