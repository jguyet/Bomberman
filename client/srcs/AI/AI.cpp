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
	this->t_last_move = TimeUtils::getCurrentSystemMillis();
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
	this->target.pos_x = 0;
	this->target.pos_y = 0;
	this->tplayer = NULL;
	this->select_t = false;

	for (auto *player : players)
	{
		float dist1 = std::abs(x - this->target.pos_x) + std::abs(y - this->target.pos_y);
		float dist2 = std::abs(x - player->transform.position.x) + std::abs(y - player->transform.position.z);
		if ((player->transform.position.x == x && player->transform.position.z == y) || (this->tplayer != NULL && dist1 < dist2))
			continue ;

		this->target.pos_x = player->transform.position.x;
		this->target.pos_y = player->transform.position.z;
		this->tplayer = player;
		this->action = ATTACK;
		this->select_t = true;
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
			// this->action = SEARCH;
			this->action = WALK;
			this->select_t = true;
		}
		this->t_last_move = TimeUtils::getCurrentSystemMillis();
	}
	else if (this->action == ATTACK && (std::abs(this->target.pos_x - this->tplayer->transform.position.x) + std::abs(this->target.pos_y - this->tplayer->transform.position.z)) > 5)
	{
		this->restart_target_pos(ATTACK);
		this->t_last_move = TimeUtils::getCurrentSystemMillis();
	}
}

int				AI::brain(void)
{
	this->bomb_l.clear();
	this->bomb_l = std::vector<BombControllerScript*>(BombControllerScript::List);

	// select && checker ###############
	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;

	this->select_target();
	if (this->start_checks())
		return (0);
	// #################################
	if (this->moves.size() > 0)
	{
		float t = SPEED; // Tolerance
		// If current target close delete them
		if (x >= this->moves.front().pos_x - t && x <= this->moves.front().pos_x + t && y >= this->moves.front().pos_y - t && y <= this->moves.front().pos_y + t)
			this->moves.pop_front();

		if (this->moves.size() == 0)
		{
			if (this->action == SEARCH || this->action == ATTACK)
			{
				// TODO : deselect target FOR path_finding
				this->restart_target_pos(ESCAPE);
				return (SDL_SCANCODE_Q);
			}
			else
				this->action = WAIT;
		}
	} else if (this->a_star.path_finding(x, y, this->target, moves, this->bomb_l, this->action) == false) {
		// std::cout << "-------------- FAIL OF PATH path_finding in action " << this->action << std::endl;
		// if (this->action == SEARCH)
		// 	this->action = END;
		// else
			this->action = WAIT;
		return (0);
	}
	// move ############################
	if (this->moves.size() > 0 &&  (this->action == WALK || this->action == SEARCH || this->action == ESCAPE || this->action == ATTACK))
	{
		if (x <= this->moves.front().pos_x && (abs(x - this->moves.front().pos_x) > SPEED))
		return(SDL_SCANCODE_UP);
		if (x > this->moves.front().pos_x && (abs(x - this->moves.front().pos_x) > SPEED))
		return(SDL_SCANCODE_DOWN);
		if (y > this->moves.front().pos_y && (abs(y - this->moves.front().pos_y) > SPEED))
		return(SDL_SCANCODE_LEFT);
		if (y < this->moves.front().pos_y && (abs(y - this->moves.front().pos_y) > SPEED))
		return(SDL_SCANCODE_RIGHT);
	}
	// #################################
	return (0);
}

// ###############################################################

// PRIVATE METHOD ################################################

int				AI::start_checks(void)
{
	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;

	// if (this->action == END)
	// 	return (1);

	long t_current = TimeUtils::getCurrentSystemMillis();
	float res = (std::abs(this->last_pos_x - x) + std::abs(this->last_pos_y - y));
	if ((this->action == WALK || this->action == SEARCH || this->action == ESCAPE || this->action == ATTACK) && res > 0.2)
	{
		if ((t_current - this->t_last_move) > 1000)
		{
			// std::cout << "-------------- TIMEOUT ESCAPE " << this->action << std::endl;
			// this->t_last_move = t_current;
			this->restart_target_pos(ESCAPE);
		}
		this->last_pos_x = this->my_player->transform.position.x;
		this->last_pos_y = this->my_player->transform.position.z;
	}
	else
		this->t_last_move = t_current;

	if (this->action == WAIT)
	{
		this->pause = TimeUtils::getCurrentSystemMillis() + 1000;
		this->action = IDLE;
		this->select_t = false;
		return (1);
	}

	if (this->moves.size() > 0 && this->a_star.bomb_col(this->bomb_l, this->moves.back().pos_x, this->moves.back().pos_y) == 0)
	{
		this->restart_target_pos(ESCAPE);
		return (1);
	}

	if (this->pause != 0)
	{
		if (this->a_star.bomb_col(this->bomb_l, my_player->transform.position.x, my_player->transform.position.z) == 0)
		{
			this->restart_target_pos(ESCAPE);
			return (0);
		}
		int n_bomb = dynamic_cast<CharacterControllerScript *>(my_player->GetComponent<Script>())->bomb;
		if (n_bomb == 0)
			return (1);

		if (this->pause < TimeUtils::getCurrentSystemMillis())
			this->pause = 0;
		return (1);
	}

	if (this->select_t == false)
		return (1);
	return (0);
}

void				AI::restart_target_pos(e_action action)
{
	if (action == ATTACK)
	{
		this->target.pos_x = this->tplayer->transform.position.x;
		this->target.pos_y = this->tplayer->transform.position.z;
	}
	this->action = action;
	this->pause = 0;
	this->moves.clear();
}

// ###############################################################
