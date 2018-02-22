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

bool						A_star::path_finding(int x, int y, Module_h &target, std::list<Module_h> &moves)
{
	moves.clear();
	//std::cout <<  "Start A star pos x" << x << " pos y "  << y << std::endl;

	///////// format
	if ((x % 2) != 0)
		x++;
	if ((y % 2) != 0)
		y++;

	if ((target.pos_x % 2) != 0)
		target.pos_x++;
	if ((target.pos_y % 2) != 0)
		target.pos_y++;
	///////////////////////////////////////

	//std::cout <<  "Start A star pos x" << x << " pos y "  << y << std::endl;

	if (this->get_heuristic(y, x, target, 0))
		return (false);

	//std::cout <<  "Start A star 2 " << std::endl;
	target.heuristic = this->open_list.top().heuristic;
	int tmp_h = target.heuristic;

	if (!this->open_list.empty())
		this->find_path(target);
	else
		return (false);

	if (this->open_list.empty())
		return (false);
	//std::cout <<  "Start A star 3 " << std::endl;

	if (this->FormatMoves(moves, target.pos_x, target.pos_y, this->close_list[std::make_pair(target.pos_x, target.pos_y)].p, x, y))
	{
		moves.push_back(this->close_list[std::make_pair(target.pos_x, target.pos_y)]);
	}

	//std::cout <<  "Start A star 4 " << std::endl;

	// if ((target.pos_x % 2) == 0 && (target.pos_y % 2) != 0)
		// moves.push_back(this->close_list[std::make_pair(target.pos_x, target.pos_y)]);

	this->close_list.clear();
	while (!this->open_list.empty())
		this->open_list.pop();
	return (true);
}

void						A_star::set_map(Map* map)
{
	this->map = map;
}

// ###############################################################

// PRIVATE METHOD ################################################

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

int							A_star::Find_next(std::list<Module_h> &moves, int x, int y, int p, int s_x, int s_y)
{
	if (this->close_list.count(std::make_pair(x, y)) != 0 && this->close_list[std::make_pair(x, y)].p == p - 1)
	{
		if (this->FormatMoves(moves, x, y, p - 1, s_x, s_y))
			return (1);
	}
	return (0);
}

int							A_star::get_heuristic(int y, int x, Module_h &target, int p)
{
	Module_h elem;
	Case *c = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(fmax(0.5f + x / 2.f, 0), fmax(0.5f + y / 2.f, 0));

	if (c->walkable == true && this->close_list.count(std::make_pair(x, y)) == 0 && (x % 2) == 0 && (y % 2) == 0)
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

void						A_star::find_path(Module_h &target)
{
	int i = 0;
	int max_i = 500;

	Module_h c_case = this->open_list.top();
	int p;
	while (c_case.pos_y != target.pos_y || c_case.pos_x != target.pos_x)
	{
		// TODO: find ERROR
		if (i == max_i || this->open_list.empty())
		{
			// std::cout <<  "Error " << std::endl;
			this->close_list.clear();
			while (!this->open_list.empty())
				this->open_list.pop();
			return ;
		}
		p = c_case.p;
		// c_case.p = c_case.p + 1;

		std::cout << " [x] > "  << c_case.pos_x <<  " [y] > "  << c_case.pos_y << " ||||||||| {x} - " << target.pos_x << " {y} - "<< target.pos_y <<  " heuristic |:> " << c_case.heuristic  << " |p| "  << p << "  size open  : " << this->open_list.size() << "  size close  : " << this->close_list.size() << std::endl;
		// UP
		get_adjacent(c_case, target, c_case.pos_x, c_case.pos_y + 2, p);
		// Down
		get_adjacent(c_case, target, c_case.pos_x, c_case.pos_y - 2, p);
		// Rhigt
		get_adjacent(c_case, target, c_case.pos_x + 2, c_case.pos_y, p);
		// Left
		get_adjacent(c_case, target, c_case.pos_x - 2, c_case.pos_y, p);

		c_case = this->open_list.top();
		this->open_list.pop();
		i++;
	}
	c_case.p++;
	this->close_list.insert(std::pair<std::pair<int, int>, Module_h>(std::make_pair(std::make_pair(c_case.pos_x, c_case.pos_y), c_case)));
	//std::cout << " [x] > "  << c_case.pos_x <<  " [y] > "  << c_case.pos_y << " ||||||||| {x} - " << target.pos_x << " {y} - "<< target.pos_y <<  " heuristic |:> " << c_case.heuristic  << " |p| "  << c_case.p << "  size open  : " << this->open_list.size() << "  size close  : " << this->close_list.size() << std::endl;
}

void						A_star::get_adjacent(Module_h c_case, Module_h &target, int x, int y, int p)
{
	if (this->map->getCase(x, y) != NULL && this->close_list.count(std::make_pair(x, y)) == 0)
		this->get_heuristic(y, x, target, p);
}

// ###############################################################
