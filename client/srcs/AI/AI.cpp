#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

AI::AI (GameObject* my_player) : my_player(my_player)
{
	this->a_star.set_map(dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->map);
	this->select_t = false;
	this->pause = 0;
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
}

void				AI::select_target(void)
{
	static int info = 0;
	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;

	if (this->select_t == false)
	{
		// this->get_target(x, y, dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->all_player);

		if (info == 0)
		{
			this->getInfos();
			info = 1;
		}

		if (this->action != SEARCH)
		{
			GameObject *near;
			near = this->getNearestBlock();

			this->target.pos_x = near->transform.position.x;
			this->target.pos_y = near->transform.position.z;
			this->tplayer = near;
			this->action = SEARCH;
			std::cout << "start x " << x << " y " << y << " t x " << target.pos_x << " t y" << target.pos_y << std::endl;
		}
		else {

		}
		this->select_t = true;
	}
	else if ((std::abs(this->target.pos_x - this->tplayer->transform.position.x) + std::abs(this->target.pos_y - this->tplayer->transform.position.z)) > 5)
		this->restart_target_pos();
}

int 				AI::getInfos(void)
{
	Scene *scene = BombermanClient::getInstance()->current_scene;

	this->Objects.clear();
	std::map<long, GameObject*>  cpy_scene = std::map<long, GameObject*>(scene->gameObjects);
	for (auto &it : cpy_scene) {
		GameObject *current = it.second;

		if (current->tag == "ice_block")
			this->Objects.push_back(current);
		// if (current->tag == "ice_block")
		// 	this->Objects.push_back(current);
	}
	return (0);
}

GameObject			*AI::getNearestBlock()
{
	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;

	float distance = 999;
	float dist;
	GameObject *near = NULL;

	for (GameObject *object : this->Objects)
	{
		dist = glm::distance(this->my_player->transform.position, object->transform.position);

		if (dist < distance) {
			distance = dist;
			near = object;
		}
	}
	return (near);
}

int				AI::bombcol(int x, int y, int next_x, int next_y)
{
	if (this->a_star.bomb_col(this->bomb_l, x, y) == 0 && this->a_star.bomb_col(this->bomb_l, this->moves.back().pos_x, this->moves.back().pos_y) == 0)
	{
		// std::cout << " DEAD :( last pos x " <<  this->moves.back().pos_x << " y " << this->moves.back().pos_y << std::endl;
		this->restart_target_pos();
		return (1);
	}
	// if (!this->a_star.bomb_col(this->bomb_l, next_x, next_y))
	// {
	// 	this->pause = 120;
	// 	// this->restart_target_pos();
	// 	return (2);
	// }
	return (0);
}

int				AI::brain(void)
{
	this->bomb_l = BombControllerScript::List;
	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;
	this->action = IDLE;

	this->select_target();
	// checker ##########################

	if (this->start_checks())
		return (0);

	// #################################

	if (this->moves.size() > 0)
	{
		float t = SPEED; // Tolerance
		//If current target close delete them
		if (x >= this->moves.front().pos_x - t && x <= this->moves.front().pos_x + t && y >= this->moves.front().pos_y - t && y <= this->moves.front().pos_y + t)
		{
			this->moves.pop_front();
			// std::cout << "target x " << this->moves.front().pos_x << " target y " << this->moves.front().pos_y << std::endl;
		}
		if (this->moves.size() == 0 || this->bombcol(x, y, this->moves.front().pos_x, this->moves.front().pos_y))
			return (0);
	} else if (this->a_star.path_finding(x, y, this->target, moves, this->bomb_l) == false) {
		return (0);
	}

	// move ############################
	if (x <= this->moves.front().pos_x && (abs(x-this->moves.front().pos_x) > SPEED))
		return(SDL_SCANCODE_UP);
	if (x > this->moves.front().pos_x && (abs(x-this->moves.front().pos_x) > SPEED))
		return(SDL_SCANCODE_DOWN);
	if (y > this->moves.front().pos_y && (abs(y-this->moves.front().pos_y) > SPEED))
		return(SDL_SCANCODE_LEFT);
	if (y < this->moves.front().pos_y && (abs(y-this->moves.front().pos_y) > SPEED))
		return(SDL_SCANCODE_RIGHT);
	// return (SDL_SCANCODE_Q);

	// #################################
	return (0);
}

// ###############################################################

// PRIVATE METHOD ################################################

int				AI::start_checks(void)
{
	if (this->tplayer != NULL && this->tplayer->tag != "ice_block")
	{
		// info = 0;
		this->select_t = false;
		std::cout << " NO ice_block :)" << std::endl;
		return (1);
	}

	if (this->select_t == false)
		return (1);

	if (this->pause)
	{
		this->pause--;
		return (1);
	}

	return (0);
}

void				AI::restart_target_pos(void)
{
	this->target.pos_x = this->tplayer->transform.position.x;
	this->target.pos_y = this->tplayer->transform.position.z;
	this->moves.clear();
}

// ###############################################################
