#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

AI::AI (GameObject* my_player) : my_player(my_player)
{
	this->a_star.set_map(BombermanClient::getInstance()->getCurrentScene<GameScene>()->map);
	this->select_t = false;
	this->pause = 0;
	this->action = IDLE;
	this->count = 150;
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
		this->last_pos_x = this->my_player->transform.position.x;
		this->last_pos_y = this->my_player->transform.position.z;
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
		std::cout << "pos target x " << player->transform.position.x << " y " << player->transform.position.z << std::endl;
		if (player->transform.position.x != x || player->transform.position.z != y)
		{
			this->target.pos_x = player->transform.position.x;
			this->target.pos_y = player->transform.position.z;
			this->tplayer = player;
			this->select_t = true;
		}
	}
}

void				AI::select_target(void)
{
	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;

	if (this->select_t == false)
	{
		// this->get_target(x, y, dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->all_player);
		if (this->action == IDLE)
		{
			this->action = SEARCH;
			this->select_t = true;
			// std::cout << "start x " << x << " y " << y << " t x " << target.pos_x << " t y" << target.pos_y << std::endl;
		}
	}
	// else if ((std::abs(this->target.pos_x - this->tplayer->transform.position.x) + std::abs(this->target.pos_y - this->tplayer->transform.position.z)) > 5)
	// 	this->restart_target_pos();
}


int				AI::brain(void)
{
	this->bomb_l.clear();
	this->bomb_l = std::vector<BombControllerScript*>(BombControllerScript::List);

	// select && checker ###############
	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;

	if (this->action == SEARCH || this->action == ESCAPE)
	{
		float res = (std::abs(this->last_pos_x - x) + std::abs(this->last_pos_y - y));
		if (res < 0.2)
			this->count--;
		else
		{
			this->count = 150;
			this->last_pos_x = this->my_player->transform.position.x;
			this->last_pos_y = this->my_player->transform.position.z;
		}
		if (this->count == 0)
			this->restart_target_pos();
	}

	this->select_target();
	if (this->start_checks())
		return (0);
	// #################################
	if (this->moves.size() > 0)
	{
		float t = SPEED; // Tolerance
		//If current target close delete them
		if (x >= this->moves.front().pos_x - t && x <= this->moves.front().pos_x + t && y >= this->moves.front().pos_y - t && y <= this->moves.front().pos_y + t)
			this->moves.pop_front();

		if (this->moves.size() == 0)
		{
			if (this->action == SEARCH)
			{
				// TODO : deselect target FOR path_finding
				this->action = ESCAPE;
				return (SDL_SCANCODE_Q);
			}
			else
			{
				this->action = WAIT;
				this->select_t = false;
			}
		}
		// else if (this->bombcol(x, y, this->moves.front().pos_x, this->moves.front().pos_y))
		// 	return (0);
	} else if (this->a_star.path_finding(x, y, this->target, moves, this->bomb_l, this->action) == false) {
		// std::cout << "-------------- FAIL OF PATH path_finding in action " << this->action << std::endl;
		this->action = WAIT;
		return (0);
	}
	// move ############################
	if (x <= this->moves.front().pos_x && (abs(x - this->moves.front().pos_x) > SPEED))
		return(SDL_SCANCODE_UP);
	if (x > this->moves.front().pos_x && (abs(x - this->moves.front().pos_x) > SPEED))
		return(SDL_SCANCODE_DOWN);
	if (y > this->moves.front().pos_y && (abs(y - this->moves.front().pos_y) > SPEED))
		return(SDL_SCANCODE_LEFT);
	if (y < this->moves.front().pos_y && (abs(y - this->moves.front().pos_y) > SPEED))
		return(SDL_SCANCODE_RIGHT);
	// #################################
	return (0);
}

// ###############################################################

// PRIVATE METHOD ################################################

int				AI::start_checks(void)
{
	if (this->action == WAIT)
	{
		this->pause = 120;
		this->action = IDLE;
		return (1);
	}

	if (this->moves.size() > 0 && this->a_star.bomb_col(this->bomb_l, this->moves.back().pos_x, this->moves.back().pos_y) == 0)
	{
		this->restart_target_pos();
		return (1);
	}

	if (this->pause)
	{
		if (this->a_star.bomb_col(this->bomb_l, my_player->transform.position.x, my_player->transform.position.z) == 0)
		{
			this->restart_target_pos();
			return (0);
		}
		int n_bomb = dynamic_cast<CharacterControllerScript *>(my_player->GetComponent<Script>())->bomb;
		if (n_bomb == 0)
			return (1);
		this->pause--;
		return (1);
	}

	if (this->select_t == false)
		return (1);
	return (0);
}

void				AI::restart_target_pos(void)
{
	// this->target.pos_x = this->tplayer->transform.position.x;
	// this->target.pos_y = this->tplayer->transform.position.z;
	this->action = ESCAPE;
	this->pause = 0;
	this->count = 150;
	this->moves.clear();
}

// ###############################################################
