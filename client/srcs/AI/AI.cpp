#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

AI::AI ( void )
{
	this->a_star.set_map(dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map);
	this->target.pos_x = 0;
	this->target.pos_y = 0;
	return ;
}

AI::AI ( AI const & src )
{
	*this = src;
	return ;
}

AI &				AI::operator=( AI const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

AI::~AI ( void )
{
	return ;
}

std::ostream &		operator<<(std::ostream & o, AI const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void				AI::get_target(int x, int y, std::vector<GameObject*> players)
{
	// TODO : get nearest target
	// std::cout << "pos x " << x << " y " << y << std::endl;
	for (auto *player : players)
	{
		// std::cout << "pos player x " << player->transform.position.x << " y " << player->transform.position.z << std::endl;
		if (player->transform.position.x != x && player->transform.position.z != y)
		{
			// std::cout << "pos target x " << player->transform.position.x << " y " << player->transform.position.z << std::endl;
			this->target.pos_x = player->transform.position.x;
			this->target.pos_y = player->transform.position.z;
			this->tplayer = player;
		}
	}
}

// std::make_pair(SDL_SCANCODE_Q, &CharacterControllerScript::Attack), std::make_pair(SDL_SCANCODE_UP, &CharacterControllerScript::MUp),
// std::make_pair(SDL_SCANCODE_DOWN, &CharacterControllerScript::MDown), std::make_pair(SDL_SCANCODE_LEFT, &CharacterControllerScript::MLeft),
// std::make_pair(SDL_SCANCODE_RIGHT, &CharacterControllerScript::MRight)
int					AI::brain(int x, int y)
{
	// static std::vector<Module_h> moves;
	// std::vector<Module_h> tmp;

	// moves.clear();
	if (this->target.pos_x == 0 && this->target.pos_y == 0)
		this->get_target(x, y, dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->players);
	else
	{
		this->target.pos_x = this->tplayer->transform.position.x;
		this->target.pos_y = this->tplayer->transform.position.z;
	}

	if (moves.size() > 0)
	{
		std::cout << "Position x >" << x << "< y >" << y << "< " << std::endl;
		std::cout << "Objective x >" << moves[0].pos_x << "< y >" << moves[0].pos_y << "< " << std::endl;

		if (x == moves[0].pos_x && y == moves[0].pos_y)
		{
			std::cout << "Objective Next objective" << std::endl;
			moves.pop_back();
		}
		else
			std::cout << "nope" << std::endl;
	}
	else if (this->a_star.path_finding(x, y, this->target, moves))
	{
		moves.pop_back();
		// int tmp_x, tmp_y;
		for (auto elem : moves)
		{
			std::cout << "-x " << elem.pos_x << " -y " << elem.pos_y <<  std::endl;
		}
	}

	if (x + 1 == moves[0].pos_x && y == moves[0].pos_y)
		return(SDL_SCANCODE_UP);
	if (x - 1 == moves[0].pos_x && y == moves[0].pos_y)
		return(SDL_SCANCODE_DOWN);
	if (x == moves[0].pos_x && y + 1 == moves[0].pos_y)
		return(SDL_SCANCODE_RIGHT);
	if (x == moves[0].pos_x && y - 1 == moves[0].pos_y)
		return(SDL_SCANCODE_LEFT);
	return (0);
}

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################
