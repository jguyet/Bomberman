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


int 				AI::getInfos(void)
{
	Scene *scene;
	scene = BombermanClient::instance->current_scene;
	for (std::map<long, GameObject*>::iterator it = scene->gameObjects.begin(); it != scene->gameObjects.end(); it++) {
		GameObject *current = it->second;
		if (current->tag == "ice_block")
		{
			//std::cout << current->tag << " " <<current->transform.position.x << " " << current->transform.position.z << std::endl;
			this->Objects.push_back(current);
		}
	}
	return (0);
}

GameObject 			*AI::getNearestBlock()
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

// int x, int y
int					AI::brain()
{
	static int info = 0;

/*

	for (GameObject *object : this->Objects)
	{
		//std::cout << " " << object->tag << object->transform.position.x << " " <<  object->transform.position.z << "" << std::endl;
	}
*/
	// moves.clear();
	float x = this->my_player->transform.position.x;
	float y = this->my_player->transform.position.z;

	int nx = moves.front().pos_x;
	int ny = moves.front().pos_y;

	if (this->select_t == false)
	{
		// this->get_target(x, y, dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->all_player);

		if (info == 0)
			this->getInfos();

		GameObject *near;
		near = this->getNearestBlock();

		std::cout << glm::distance(this->my_player->transform.position, near->transform.position) << std::endl;

		this->target.pos_x = near->transform.position.x;
		this->target.pos_y = near->transform.position.z + 2;
		this->tplayer = near;
		this->select_t = true;
	}
	else
	{
		this->target.pos_x = this->tplayer->transform.position.x;
		this->target.pos_y = this->tplayer->transform.position.z;
	}

	if (this->tplayer != NULL && this->tplayer->tag != "ice_block")
	{
		info = 0;
		this->select_t = false;
		std::cout << " NO ice_block :)" << std::endl;
	}

	if (this->select_t == false)
		return (0);

	if (moves.size() > 0)
	{
		float t = SPEED; // Tolerance
		//If current target close delete them
		if (x >= nx - t && x <= nx + t && y >= ny - t && y <= ny + t)
			moves.pop_front();
	} else if (this->a_star.path_finding(x, y, this->target, moves) == false){
		return (0);
	}

	if (x <= nx && (abs(x-nx) > SPEED) )
		return(SDL_SCANCODE_UP);
	if (x > nx && (abs(x-nx) > SPEED))
		return(SDL_SCANCODE_DOWN);
	if (y > ny && (abs(y-ny) > SPEED))
		return(SDL_SCANCODE_LEFT);
	if (y < ny && (abs(y-ny) > SPEED))
		return(SDL_SCANCODE_RIGHT);

	return (SDL_SCANCODE_Q);
	return (0);
}

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################
