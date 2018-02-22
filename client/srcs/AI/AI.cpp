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

void				AI::get_target(float x, float y, std::vector<GameObject*> players)
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
	// moves.clear();
	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;

	int nx = moves.front().pos_x;
	int ny = moves.front().pos_y;

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
		float t = SPEED; // Tolerance
		//If current target close delete them
		if (x >= nx - t && x <= nx + t && y >= ny - t && y <= ny + t)
			moves.pop_front();
	} else {
		this->a_star.path_finding(x, y, this->target, moves);
	}

	if (x <= nx && (abs(x-nx) > SPEED) )
		return(SDL_SCANCODE_UP);
	if (x > nx && (abs(x-nx) > SPEED))
		return(SDL_SCANCODE_DOWN);
	if (y > ny && (abs(y-ny) > SPEED))
		return(SDL_SCANCODE_LEFT);
	if (y < ny && (abs(y-ny) > SPEED))
		return(SDL_SCANCODE_RIGHT);

	return (0);
}

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################
