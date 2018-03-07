#include "Bomberman.hpp"

// STATIC ########################################################
// ###############################################################

// CANONICAL #####################################################

A_star::A_star ( void )
{
	return ;
}

A_star::A_star ( A_star const & src )
{
	*this = src;
	return ;
}

A_star &				A_star::operator=( A_star const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

A_star::~A_star ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, A_star const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

bool						A_star::path_finding(int x, int y, Module_h &target, std::list<Module_h> &moves, std::vector<BombControllerScript*> &bomb_l, e_action action)
{
	moves.clear();
	this->bomb_list = bomb_l;

	this->init_var(x, y, target, action);
	// std::cout << "start x " << x << " y " << y << " t x " << target.pos_x << " t y" << target.pos_y << std::endl;
	if (this->get_heuristic(y, x, target, 0, action))
		return (false);

	target.heuristic = this->open_list.top().heuristic;
	int tmp_h = target.heuristic;

	this->find_path(target, action);
	if (this->close_list.empty())
		return (false);

	this->FormatMoves(moves, target.pos_x, target.pos_y, this->close_list[std::make_pair(target.pos_x, target.pos_y)].p, x, y);
	if (action == ESCAPE)
		moves.push_back(this->close_list[std::make_pair(target.pos_x, target.pos_y)]);

	this->delete_lists();
	// for (auto &elem : moves)
	// {
	// 	std::cout << "-x " << elem.pos_x << " -y " << elem.pos_y << std::endl;
	// }
	return (true);
}

void						A_star::set_map(Map* map)
{
	this->map = map;
}

// ###############################################################

// PRIVATE METHOD ################################################

void						A_star::get_adjacent(Module_h &c_case, Module_h &target, e_action action, int x, int y, int p)
{
	if (this->map->getCase(x, y) != NULL && this->close_list.count(std::make_pair(x, y)) == 0)
		this->get_heuristic(y, x, target, p, action);
}

int							A_star::stop_condition(Module_h &c_case, Module_h &target, e_action action)
{
	GameScene *scene = BombermanClient::getInstance()->getCurrentScene<GameScene>();
	bool ice = false;
	if (!scene)
		return (0);
	Case *c = scene->map->getCase(fmax(0.5f + c_case.pos_x / 2.f, 0), fmax(0.5f + c_case.pos_y / 2.f, 0));
	if (c->obstacle && c->obstacle->tag == "destructible_block")
		ice = true;

	if (action == ATTACK && (c_case.pos_y != target.pos_y || c_case.pos_x != target.pos_x))
		return (1);
	else if (action == ESCAPE && this->bomb_col(this->bomb_list, c_case.pos_x, c_case.pos_y) == 0)
	{
		return (1);
	}
	else if (action == SEARCH && ice == false) // this->bomb_col(this->bomb_list, c_case.pos_x, c_case.pos_y) == 0
	{
		return (1);
	}

	if (action == ESCAPE || action == SEARCH)
	{
		target.pos_x = c_case.pos_x;
		target.pos_y = c_case.pos_y;
	}
	return (0);
}

void						A_star::find_path(Module_h &target, e_action action)
{
	int i = 0;
	int max_i = 250;

	Module_h c_case = this->open_list.top();
	int p;
	while (this->stop_condition(c_case, target, action))
	{
		p = c_case.p;
		// UP
		get_adjacent(c_case, target, action, c_case.pos_x, c_case.pos_y + 2, p);
		// Down
		get_adjacent(c_case, target, action, c_case.pos_x, c_case.pos_y - 2, p);
		// Rhigt
		get_adjacent(c_case, target, action, c_case.pos_x + 2, c_case.pos_y, p);
		// Left
		get_adjacent(c_case, target, action, c_case.pos_x - 2, c_case.pos_y, p);

		if (i == max_i || this->open_list.empty())
		{
			// std::cout << ">>>>>>>>>>>>>>>> int  " << i << std::endl;
			this->delete_lists();
			return ;
		}
		c_case = this->open_list.top();
		this->open_list.pop();
		i++;
	}
	c_case.p++;
	this->close_list.insert(std::pair<std::pair<int, int>, Module_h>(std::make_pair(std::make_pair(c_case.pos_x, c_case.pos_y), c_case)));
}

int							A_star::Find_next(std::list<Module_h> &moves, int x, int y, int p, int s_x, int s_y)
{
	if (this->close_list.count(std::make_pair(x, y)) != 0 && this->close_list[std::make_pair(x, y)].p == p - 1)
	{
		if (this->FormatMoves(moves, x, y, p - 1, s_x, s_y))
			return (1);
	}
	return (0);
}

int 						A_star::FormatMoves(std::list<Module_h> &moves, int x, int y, int p, int s_x, int s_y)
{
	if (x == s_x && y == s_y)
		return (1);

	if (this->Find_next(moves, x + 2, y,  p, s_x, s_y))
	{
		moves.push_back(this->close_list[std::make_pair(x + 2, y)]);
		return (1);
	}
	if (this->Find_next(moves, x - 2, y,  p, s_x, s_y))
	{
		moves.push_back(this->close_list[std::make_pair(x - 2, y)]);
		return (1);
	}
	if (this->Find_next(moves, x, y + 2,  p, s_x, s_y))
	{
		moves.push_back(this->close_list[std::make_pair(x, y + 2)]);
		return (1);
	}
	if (this->Find_next(moves, x, y - 2,  p, s_x, s_y))
	{
		moves.push_back(this->close_list[std::make_pair(x, y - 2)]);
		return (1);
	}
	return (0);
}

int							A_star::get_heuristic(int y, int x, Module_h &target, int p, e_action action)
{
	Module_h elem;
	bool flag_t = false;
	GameScene *scene = BombermanClient::getInstance()->getCurrentScene<GameScene>();
	if (!scene)
		return (0);

	Case *c = scene->map->getCase(fmax(0.5f + x / 2.f, 0), fmax(0.5f + y / 2.f, 0));
	if ((x == target.pos_x && y == target.pos_y) || (x == this->start.pos_x && y == this->start.pos_y) || (action == SEARCH && c->obstacle && c->obstacle->tag == "destructible_block"))
		flag_t = true;

	if ((c->walkable == true || flag_t) && (x % 2) == 0 && (y % 2) == 0)
	{
		int dif_x = std::abs(x - target.pos_x);
		int dif_y = std::abs(y - target.pos_y);
		elem.heuristic = dif_x + dif_y;
		elem.pos_x = x;
		elem.pos_y = y;
		elem.p = p + 1;
		this->open_list.push(elem);
		this->close_list.insert(std::pair<std::pair<int, int>, Module_h>(std::make_pair(std::make_pair(x, y), elem)));
		return (0);
	}
	else
		return (1);
}

int							A_star::bomb_col(std::vector<BombControllerScript*> bomb_l, float x, float y)
{
	float t = SPEED; // Tolerance

	for (auto &elem : bomb_l)
	{
		float powe = elem->power * 2;
		// long rest_time = BOMB_TIME - (TimeUtils::getCurrentSystemMillis() - elem->startTime);

		// if (rest_time > 1000)
		// 	continue;
		float tx = elem->gameObject->transform.position.x;
		float ty = elem->gameObject->transform.position.z;
		if (x >= tx - t && x <= tx + t + powe && y >= ty - 1.0f - t && y <= ty + 1.0f + t)
		return (0);

		if (x >= tx - t - powe && x <= tx + t && y >= ty - 1.0f - t && y <= ty + 1.0f + t)
		return (0);

		if (x >= tx - 1.0f - t && x <= tx + 1.0f + t && y >= ty - t && y <= ty + t + powe)
		return (0);

		if (x >= tx - 1.0f - t && x <= tx + 1.0f + t && y >= ty - t - powe  && y <= ty + t)
		return (0);
	}
	return (1);
}

void						A_star::delete_lists(void)
{
	this->close_list.clear();
	while (!this->open_list.empty())
		this->open_list.pop();
}

void						A_star::init_var(int &x, int &y, Module_h &target, e_action action)
{
	if ((x % 2) != 0)
		x++;
	if ((y % 2) != 0)
		y++;

	if (action == ESCAPE || action == SEARCH)
	{
		target.pos_x = ((rand() % 2) == 1) ? 10000 : -10000;
		target.pos_y = ((rand() % 2) == 1) ? 10000 : -10000;
	}
	else
	{
		if ((target.pos_x % 2) != 0)
			target.pos_x++;
		if ((target.pos_y % 2) != 0)
			target.pos_y++;
	}

	this->start.pos_x = x;
	this->start.pos_y = y;
}

// ###############################################################
