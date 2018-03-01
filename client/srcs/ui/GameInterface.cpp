#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

GameInterface::GameInterface ( GameScene *scene ) : UIInterface("themes/GameInterface.html")
{
	this->scene = scene;
	this->canvas = new Canvas(BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height);
	this->canvas->setElementsMap(&this->elements);
	return ;
}

GameInterface::GameInterface ( GameInterface const & src ) : UIInterface("")
{
	*this = src;
	return ;
}

GameInterface &				GameInterface::operator=( GameInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameInterface::~GameInterface ( void )
{
	delete this->canvas;
	return ;
}

std::ostream &				operator<<(std::ostream & o, GameInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						GameInterface::addPlayers(void)
{
	std::vector<GameObject*>	players = std::vector<GameObject*>(this->scene->players);

	int order = 1;
	for (int i = 0; i < players.size(); i++)
	{
		GameObject *player = players.at(i);

		if (player == NULL)
			continue ;
		CharacterControllerScript *script = ((CharacterControllerScript*)player->GetComponent<Script>());
		if (script == NULL)
			continue ;
		std::string key = (std::ostringstream() << "$player_name" << order).str();

		std::string player_name;

		if (script->playerId == 100) {
			player_name = (std::ostringstream() << "bot (" << player->id << ")").str();
		} else {
			player_name = (std::ostringstream() << "player (" << script->playerId << ")").str();
		}
		this->variables[key] = player_name;
		order++;
	}

	for (; order < 8; order++)
	{
		std::string key = (std::ostringstream() << "$player_name" << order).str();
		this->variables[key] = "";
	}
}

void						GameInterface::draw(void)
{
	std::string bomb_value = "0";
	std::string power_value = "0";
	std::string speed_value = "0";
	std::string player_name = "";
	if (this->scene->current_player != NULL) {
		CharacterControllerScript *script = ((CharacterControllerScript*)this->scene->current_player->GetComponent<Script>());
		if (script != NULL) {
			bomb_value = (std::ostringstream() << script->bomb).str();
			power_value = (std::ostringstream() << script->power).str();
			speed_value = (std::ostringstream() << script->speed_count).str();
			player_name = (std::ostringstream() << script->playerId).str();
		}
	}
	this->variables["$bomb"] = bomb_value;
	this->variables["$power"] = power_value;
	this->variables["$speed"] = speed_value;
	this->variables["$current_player_name"] = player_name;

	this->build();
	this->canvas->draw();
}

// ###############################################################
