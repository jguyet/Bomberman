#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

AI::AI (GameObject* my_player, int level) : my_player(my_player), level(level)
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
		this->level = rhs.level;
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

	// this->select_t == false ||
	if ( this->action == IDLE)
	{
		int rand_action = rand() % this->level + 1;

		// std::cout << "select action " << rand_action << std::endl;

		if (rand_action <= 1)
			this->action = WALK;
		else if (rand_action <= 5)
			this->action = SEARCH;
		else
			this->get_target(x, y, dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->all_player);

		this->select_t = true;
		this->set_last_move();
	}
	else if (this->action == ATTACK && (std::abs(this->target.pos_x - this->tplayer->transform.position.x) + std::abs(this->target.pos_y - this->tplayer->transform.position.z)) > 5)
	{
		this->restart_target_pos(ATTACK);
		this->set_last_move();
	}
}

int				AI::move(float x, float y)
{
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
	return (0);
}

int				AI::brain(void)
{
	this->bomb_l.clear();
	this->bomb_l = std::vector<BombControllerScript*>(BombControllerScript::List);

	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;

	// select && checker ###############
	this->select_target();
	if (this->start_checks())
		return (0);
	// #################################

	if (this->set_next_move(x, y))
	{
		if (this->moves.size() ==  0)
		{
			if (this->action == SEARCH || this->action == ATTACK)
			{
				this->restart_target_pos(ESCAPE);
				return (SDL_SCANCODE_Q);
			}
			else
			{
				// this->restart_target_pos(IDLE);
				int n_bomb = dynamic_cast<CharacterControllerScript *>(my_player->GetComponent<Script>())->bomb;
				this->pause = (n_bomb != 0) ? TimeUtils::getCurrentSystemMillis() + 300 : TimeUtils::getCurrentSystemMillis() + BOMB_TIME;
				this->action = WAIT;
				return (0);
			}
		}
	}
	else if (this->start_path_finding(x, y))
	{
		return (0);
	}

	// #################################
	return (this->move(x, y));
}

// ###############################################################

// PRIVATE METHOD ################################################

int				AI::start_path_finding(float x, float y)
{
	this->set_last_move();
	if (this->a_star.path_finding(x, y, this->target, moves, this->bomb_l, this->action) == false)
	{
		// std::cout << "-------------- FAIL OF PATH path_finding in action " << this->action << std::endl;
		this->restart_target_pos(IDLE);
		// this->pause = TimeUtils::getCurrentSystemMillis() + 600 + BOMB_TIME;
		// this->action = WAIT;
		return (1);
	}
	return (0);
}

int					AI::set_next_move(float x, float y)
{
	float t = SPEED; // Tolerance

	if (this->moves.size() == 0)
		return (0);
	// If current target close delete them
	if (x >= this->moves.front().pos_x - t && x <= this->moves.front().pos_x + t && y >= this->moves.front().pos_y - t && y <= this->moves.front().pos_y + t)
		this->moves.pop_front();

	return (1);
}

int					AI::start_checks(void)
{
	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;

	long t_current = TimeUtils::getCurrentSystemMillis();
	float dif = (std::abs(this->last_pos_x - x) + std::abs(this->last_pos_y - y));
	if ((this->action == WALK || this->action == SEARCH || this->action == ESCAPE || this->action == ATTACK) && dif <= 0.02)
	{
		// std::cout << "-------------- RES " << dif << " action  " << this->action <<  " time diff " << (t_current - this->t_last_move) << std::endl;
		if ((t_current - this->t_last_move) > 400)
		{
			// std::cout << "-------------- TIMEOUT ESCAPE " << this->action << std::endl;
			this->set_last_move();
			this->restart_target_pos(ESCAPE);
			return (0);
		}
		this->last_pos_x = this->my_player->transform.position.x;
		this->last_pos_y = this->my_player->transform.position.z;
	}
	else
		this->set_last_move();

	if (this->moves.size() > 0 && this->a_star.bomb_col(this->bomb_l, this->moves.back().pos_x, this->moves.back().pos_y) == 0)
	{
		this->restart_target_pos(ESCAPE);
		return (0);
	}

	if (this->action == WAIT)
	{
		if (this->a_star.bomb_col(this->bomb_l, my_player->transform.position.x, my_player->transform.position.z) == 0)
		{
			this->restart_target_pos(ESCAPE);
			return (0);
		}
		int n_bomb = dynamic_cast<CharacterControllerScript *>(my_player->GetComponent<Script>())->bomb;
		if (n_bomb == 0 || this->pause > TimeUtils::getCurrentSystemMillis())
			return (1);
		this->action = IDLE;
		this->select_t = false;
		this->set_last_move();
		return (1);
	}

	if (this->select_t == false)
		return (1);
	return (0);
}

void				AI::set_last_move(void)
{
	this->t_last_move = TimeUtils::getCurrentSystemMillis();
	this->last_pos_x = this->my_player->transform.position.x;
	this->last_pos_y = this->my_player->transform.position.z;
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
