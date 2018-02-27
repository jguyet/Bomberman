#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

AI::AI (GameObject* my_player) : my_player(my_player)
{
	this->a_star.set_map(dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->map);
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
}

int 				AI::getInfos(void)
{
	Scene *scene;
	scene = BombermanClient::getInstance()->current_scene;
	for (std::map<long, GameObject*>::iterator it = scene->gameObjects.begin(); it != scene->gameObjects.end(); it++) {
		GameObject *current = it->second;
		if (current->tag == "ice_block")
		{
			// std::cout << current->tag << " " <<current->transform.position.x << " " << current->transform.position.z << std::endl;
			this->Objects.push_back(current);
		}
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

void				AI::bomblist(void)
{
	this->bomb_l = BombControllerScript::List;

	// float x = this->gameObject->transform.position.x;
	// float y = this->gameObject->transform.position.z;
	// float t = SPEED; // Tolerance
    //
	// for (auto &elem : this->bomb_l)
	// {
	// 	float powe = elem->power * 2;
	// 	if (x >= elem->gameObject->transform.position.x - t && x <= elem->gameObject->transform.position.x + t + powe &&
	// 		y >= elem->gameObject->transform.position.z - 1.0f - t && y <= elem->gameObject->transform.position.z + 1.0f + t)
	// 	{
	// 		std::cout << "hit bomb x+ X:" << this->gameObject->transform.position.x << " Z:" << this->gameObject->transform.position.z << " " << std::endl;
	// 	}
    //
	// 	if (x >= elem->gameObject->transform.position.x - t - powe && x <= elem->gameObject->transform.position.x + t &&
	// 		y >= elem->gameObject->transform.position.z - 1.0f - t && y <= elem->gameObject->transform.position.z + 1.0f + t)
	// 	{
	// 		std::cout << "hit bomb x- X:" << this->gameObject->transform.position.x << " Z:" << this->gameObject->transform.position.z << " " << std::endl;
	// 	}
    //
	// 	if (x >= elem->gameObject->transform.position.x - 1.0f - t && x <= elem->gameObject->transform.position.x + 1.0f + t &&
	// 		y >= elem->gameObject->transform.position.z - t && y <= elem->gameObject->transform.position.z + t + powe)
	// 	{
	// 		std::cout << "hit bomb y+ X:" << this->gameObject->transform.position.x << " Z:" << this->gameObject->transform.position.z << " " << std::endl;
	// 	}
    //
	// 	if (x >= elem->gameObject->transform.position.x - 1.0f - t && x <= elem->gameObject->transform.position.x + 1.0f + t &&
	// 		y >= elem->gameObject->transform.position.z - t - powe  && y <= elem->gameObject->transform.position.z + t)
	// 	{
	// 		std::cout << "hit bomb y- X:" << this->gameObject->transform.position.x << " Z:" << this->gameObject->transform.position.z << " " << std::endl;
	// 	}
	// }
}

int					AI::brain(void)
{
	static int info = 0;

	// this->bomblist();
	this->bomb_l = BombControllerScript::List;


	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;
	// this->moves.clear();

	if (this->select_t == false)
	{
		this->get_target(x, y, dynamic_cast<GameScene*>(BombermanClient::getInstance()->current_scene)->all_player);
		// this->get_target(x, y, dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->players);

		// if (info == 0)
		// 	this->getInfos();
        //
		// GameObject *near;
		// near = this->getNearestBlock();
        //
		// std::cout << glm::distance(this->my_player->transform.position, near->transform.position) << std::endl;
        //
		// this->target.pos_x = near->transform.position.x;
		// this->target.pos_y = near->transform.position.z + 2;
		// this->tplayer = near;
		// this->select_t = true;
	}
	else
	{
		this->target.pos_x = this->tplayer->transform.position.x;
		this->target.pos_y = this->tplayer->transform.position.z;
	}

	// if (this->tplayer != NULL && this->tplayer->tag != "ice_block")
	// {
	// 	info = 0;
	// 	this->select_t = false;
	// 	std::cout << " NO ice_block :)" << std::endl;
	// }

	if (this->select_t == false)
		return (0);

	if (this->moves.size() > 0)
	{
		float t = SPEED; // Tolerance
		//If current target close delete them
		if (x >= this->moves.front().pos_x - t && x <= this->moves.front().pos_x + t && y >= this->moves.front().pos_y - t && y <= this->moves.front().pos_y + t)
		{
			this->moves.pop_front();
			// std::cout << "target x " << this->moves.front().pos_x << " target y " << this->moves.front().pos_y << std::endl;
		}

		if (this->moves.size() == 0 || !this->a_star.bomb_col(this->bomb_l, x, y))
			return (0);
	} else if (this->a_star.path_finding(x, y, this->target, moves, this->bomb_l) == false){
		return (0);
	}

	if (x <= this->moves.front().pos_x && (abs(x-this->moves.front().pos_x) > SPEED))
		return(SDL_SCANCODE_UP);
	if (x > this->moves.front().pos_x && (abs(x-this->moves.front().pos_x) > SPEED))
		return(SDL_SCANCODE_DOWN);
	if (y > this->moves.front().pos_y && (abs(y-this->moves.front().pos_y) > SPEED))
		return(SDL_SCANCODE_LEFT);
	if (y < this->moves.front().pos_y && (abs(y-this->moves.front().pos_y) > SPEED))
		return(SDL_SCANCODE_RIGHT);

	// return (SDL_SCANCODE_Q);
	return (0);
}

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################
