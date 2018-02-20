#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

AI::AI ( void )
{
	this->a_star.set_map(dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map);
	this->select_t = false;
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
	std::cout << "pos x " << x << " y " << y << " Nbr players " << players.size() << std::endl;
	for (auto *player : players)
	{
		// std::cout << "pos player x " << player->transform.position.x << " y " << player->transform.position.z << std::endl;
		if (player->transform.position.x != x || player->transform.position.z != y)
		{
			// std::cout << "pos target x " << player->transform.position.x << " y " << player->transform.position.z << std::endl;
			this->target.pos_x = player->transform.position.x;
			this->target.pos_y = player->transform.position.z;
			this->tplayer = player;
			this->select_t = true;
		}
	}
	// std::cout << ">>>>>>>>>>>> pos target x " << this->target.pos_x << " y " << this->target.pos_y << std::endl;
}

// std::make_pair(SDL_SCANCODE_Q, &CharacterControllerScript::Attack), std::make_pair(SDL_SCANCODE_UP, &CharacterControllerScript::MUp),
// std::make_pair(SDL_SCANCODE_DOWN, &CharacterControllerScript::MDown), std::make_pair(SDL_SCANCODE_LEFT, &CharacterControllerScript::MLeft),
// std::make_pair(SDL_SCANCODE_RIGHT, &CharacterControllerScript::MRight)
int					AI::brain(int x, int y)
{
	// static std::vector<Module_h> moves;
	// std::vector<Module_h> tmp;

	// moves.clear();
	if (this->select_t == false)
		this->get_target(x, y, dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->players);
	else
	{
		this->target.pos_x = this->tplayer->transform.position.x;
		this->target.pos_y = this->tplayer->transform.position.z;
	}

	if (this->select_t == false)
		return (0);

	// std::cout << moves.size() << std::endl;
	if (moves.size() > 0)
	{
		// std::cout << "Objective x >" << moves[0].pos_x << "< y >" << moves[0].pos_y << "< ------" << "Position x >" << x << "< y >" << y << "< " << "size " << moves.size() << std::endl;
		if (x == moves.front().pos_x && y == moves.front().pos_y)
		{
			// std::cout << "Objective Next objective" << std::endl;
			// do {
				moves.pop_front();
			// }
			// while (((moves.front().pos_x % 2) != 0 || (moves.front().pos_y % 2) != 0) && moves.size() > 0);
		}
		// else
	}
	else if (this->a_star.path_finding(x, y, this->target, moves))
	{
		if (moves.size() > 0)
		{
			// std::cout << ">>>>>>x " << moves.front().pos_x << " >>>>>>y " << moves.front().pos_y << std::endl;
			moves.pop_front();
		}
		// for (auto elem : moves)
		// {
		// 	std::cout << "-x " << elem.pos_x << " -y " << elem.pos_y <<  std::endl;
		// }
	}

	// if (x == moves[0].pos_x && y == moves[0].pos_y)
	// {
	// 	// std::cout << "Objective Next objective" << std::endl;
	// 	// moves.pop_front();
	// }

	// for (auto elem : moves)
	// {
	// 	std::cout << ">>>>>>x " << elem.pos_x << " >>>>>>y " << elem.pos_y <<  std::endl;
	// }
	// std::cout <<  std::endl;

	// if (this->last_move == SDL_SCANCODE_UP)
	// 	x--;
	// else if (this->last_move == SDL_SCANCODE_DOWN)
	// 	x++;

	if (x < moves.front().pos_x)
	{
		this->last_move = SDL_SCANCODE_UP;
		return(SDL_SCANCODE_UP);
	}
	else if (x > moves.front().pos_x)
	{
		this->last_move = SDL_SCANCODE_DOWN;
		return(SDL_SCANCODE_DOWN);
	}
	else if (y < moves.front().pos_y)
	{
		this->last_move = SDL_SCANCODE_RIGHT;
		return(SDL_SCANCODE_RIGHT);
	}
	else if ( y > moves.front().pos_y)
	{
		this->last_move = SDL_SCANCODE_LEFT;
		return(SDL_SCANCODE_LEFT);
	}
	// else if (moves.size() > 0)
	// 	moves.pop_front();

	return (0);
}

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################
