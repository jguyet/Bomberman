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
	if (this->modified == true) {
		this->canvas->setElementsMap(&this->elements);
	}
	this->canvas->draw();
}

// ###############################################################
