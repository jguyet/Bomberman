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
	this->build();

	std::string value = "0";
	if (this->scene->current_player != NULL) {
		CharacterControllerScript *script = ((CharacterControllerScript*)this->scene->current_player->GetComponent<Script>());
		if (script != NULL) {
			std::ostringstream os;
			os << script->bomb;
			value = os.str();
		}
	}
	this->variables["$bomb"] = value;
	
	this->canvas->draw();
}

// ###############################################################
