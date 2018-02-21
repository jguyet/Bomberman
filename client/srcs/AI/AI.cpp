#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

AI::AI (GameObject* my_player) : my_player(my_player)
{
	this->a_star.set_map(dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map);
	this->select_t = false;
	return ;
}

AI::AI ( void )
{
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
		this->my_player = rhs.my_player;
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

	// std::cout << "pos x " << x << " y " << y << " Nbr players " << players.size() << std::endl;
	for (auto *player : players)
	{
		if (player->transform.position.x != x || player->transform.position.z != y)
		{
			std::cout << "pos target x " << player->transform.position.x << " y " << player->transform.position.z << std::endl;
			this->target.pos_x = player->transform.position.x;
			this->target.pos_y = player->transform.position.z;
			this->tplayer = player;
			this->select_t = true;
		}
	}
	// std::cout << ">>>>>>>>>>>> pos target x " << this->target.pos_x << " y " << this->target.pos_y << std::endl;
}

// int x, int y
int					AI::brain()
{
	// static std::vector<Module_h> moves;
	// std::vector<Module_h> tmp;

	// moves.clear();
	int x = this->my_player->transform.position.x;
	int y = this->my_player->transform.position.z;

	if (this->select_t == false)
		this->get_target(x, y, dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->all_player);
	else
	{
		this->target.pos_x = this->tplayer->transform.position.x;
		this->target.pos_y = this->tplayer->transform.position.z;
	}

	if (this->select_t == false)
		return (0);

	if (moves.size() > 0)
	{
		// if (this->my_player->transform.position.x < moves.front().pos_x + 0.02f &&
		// this->my_player->transform.position.x > moves.front().pos_x - 0.02f &&
		// this->my_player->transform.position.z < moves.front().pos_y + 0.02f &&
		// this->my_player->transform.position.z > moves.front().pos_y - 0.02f)

		if (this->my_player->transform.position.x == moves.front().pos_x + 0.0f && this->my_player->transform.position.z == moves.front().pos_y + 0.0f)
		{
			moves.pop_front();
		}
	}
	else if (this->a_star.path_finding(x, y, this->target, moves))
	{
		if (moves.size() > 0)
			moves.pop_front();
		for (auto elem : moves)
		{
			std::cout << "-x " << elem.pos_x << " -y " << elem.pos_y <<  std::endl;
		}
	}

	// std::cout << "size  " << moves.size() << std::endl;

	std::cout << "|||||pos objective -x  " << moves.front().pos_x << " -y  " << moves.front().pos_y <<  std::endl;
	std::cout << "pos float -x " << (this->my_player->transform.position.x) << " -y " << (this->my_player->transform.position.z)  <<  std::endl;
	std::cout << "pos -x " << (int)(fmax(this->my_player->transform.position.x, 1) ) << " -y " << (int)(this->my_player->transform.position.z)  <<  std::endl;

	// std::cout << "|||||pos objective -x  " << moves.front().pos_x * 100 << " -y  " << moves.front().pos_y * 100 <<  std::endl;


	// if (this->my_player->transform.position.x < moves.front().pos_x + 0.0f && (int)( fmax(this->my_player->transform.position.z, 0) * 100) == moves.front().pos_y * 100)
	// 	return (SDL_SCANCODE_UP);
	// else if (this->my_player->transform.position.x > moves.front().pos_x + 0.0f && (int)( fmax(this->my_player->transform.position.z, 0) * 100) == moves.front().pos_y * 100)
	// 	return (SDL_SCANCODE_DOWN);
	// else if ((int)(fmax(this->my_player->transform.position.x, 0) * 100) == moves.front().pos_x * 100 && this->my_player->transform.position.z > moves.front().pos_y + 0.0f)
	// 	return (SDL_SCANCODE_LEFT);
	// else if ((int)(fmax(this->my_player->transform.position.x, 0) * 100) == moves.front().pos_x * 100 && this->my_player->transform.position.z < moves.front().pos_y + 0.0f)
	// 	return (SDL_SCANCODE_RIGHT);

	if (this->my_player->transform.position.x < moves.front().pos_x + 0.0f && y == moves.front().pos_y)
		return(SDL_SCANCODE_UP);
	else if (this->my_player->transform.position.x > moves.front().pos_x + 0.0f && y == moves.front().pos_y)
		return(SDL_SCANCODE_DOWN);
	else if (x == moves.front().pos_x && this->my_player->transform.position.z > moves.front().pos_y + 0.0f)
		return(SDL_SCANCODE_LEFT);
	else if (x == moves.front().pos_x && this->my_player->transform.position.z < moves.front().pos_y + 0.0f)
		return(SDL_SCANCODE_RIGHT);

	return (0);
}

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################
