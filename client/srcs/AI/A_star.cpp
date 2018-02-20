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

bool						A_star::path_finding(int x, int y, Module_h &target, std::vector<Module_h> &moves)
{
	moves.clear();
	this->get_heuristic(y, x, target, 0);
	target.heuristic = this->open_list.top().heuristic;
	int tmp_h = target.heuristic;

	if (!this->open_list.empty())
		this->find_path(target);
	else
		return (false);

	this->FormatMoves(moves, target.pos_x, target.pos_y, 0, x, y);
	moves.push_back(this->close_list[std::make_pair(target.pos_x, target.pos_y)]);

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

int 						A_star::FormatMoves(std::vector<Module_h> &moves, int x, int y, int p, int s_x, int s_y)
{
	if (x == s_x && y == s_y)
		return (1);

	// std::cout << "------------------------ size[0] "  << moves.size() << "||| x " << x << " y "  << y << " h " << h << std::endl;
	if (this->Find_next(moves, x + 1, y,  p, s_x, s_y))
	{
		moves.push_back(this->close_list[std::make_pair(x + 1, y)]);
		return (1);
	}
	if (this->Find_next(moves, x - 1, y,  p, s_x, s_y))
	{
		moves.push_back(this->close_list[std::make_pair(x - 1, y)]);
		return (1);
	}
	if (this->Find_next(moves, x, y + 1,  p, s_x, s_y))
	{
		moves.push_back(this->close_list[std::make_pair(x, y + 1)]);
		return (1);
	}
	if (this->Find_next(moves, x, y - 1,  p, s_x, s_y))
	{
		moves.push_back(this->close_list[std::make_pair(x, y - 1)]);
		return (1);
	}
	return (0);
}

int							A_star::Find_next(std::vector<Module_h> &moves, int x, int y, int p, int s_x, int s_y)
{
	if (this->close_list.count(std::make_pair(x, y)) != 0 && this->close_list[std::make_pair(x, y)].heuristic == p + 1)
	{
		if (this->FormatMoves(moves, x, y, p + 1, s_x, s_y))
			return (1);
	}
	return (0);
}

void						A_star::get_heuristic(int y, int x, Module_h &target, int p)
{
	Module_h elem;
	Case *c = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene)->map->getCase(fmax(0.5f + x / 2.f, 0), fmax(0.5f + y / 2.f, 0));

	if (c->walkable == true)
	{
		int dif_x = std::abs(x - target.pos_x);
		int dif_y = std::abs(y - target.pos_y);
		elem.heuristic = dif_x + dif_y;
		elem.pos_x = x;
		elem.pos_y = y;
		elem.p = p + 1;
		this->open_list.push(elem);
	}
}

void						A_star::find_path(Module_h &target)
{
	Module_h c_case = this->open_list.top();
	int p;
	while (c_case.pos_y != target.pos_y || c_case.pos_x != target.pos_x)
	{
		if (this->open_list.empty())
			return ;
		p = c_case.p;
		this->close_list.insert(std::pair<std::pair<int, int>, Module_h>(std::make_pair(std::make_pair(c_case.pos_x, c_case.pos_y), c_case)));
		this->open_list.pop();

		std::cout << " [x] > "  << c_case.pos_x <<  " [y] > "  << c_case.pos_y << " ||||||||| {x} - " << target.pos_x << " {y} - "<< target.pos_y <<  " heuristic |:> " << c_case.heuristic  << "  size open  : " << this->open_list.size() << "  size close  : " << this->close_list.size() << std::endl;

		// UP
		get_adjacent(c_case, target, c_case.pos_x, c_case.pos_y + 1, p);
		// Down
		get_adjacent(c_case, target, c_case.pos_x, c_case.pos_y - 1, p);
		// Rhigt
		get_adjacent(c_case, target, c_case.pos_x + 1, c_case.pos_y, p);
		// Left
		get_adjacent(c_case, target, c_case.pos_x - 1, c_case.pos_y, p);

		c_case = this->open_list.top();
	}
	this->close_list.insert(std::pair<std::pair<int, int>, Module_h>(std::make_pair(std::make_pair(c_case.pos_x, c_case.pos_y), c_case)));
	std::cout << " [x] > "  << c_case.pos_x <<  " [y] > "  << c_case.pos_y << " ||||||||| {x} - " << target.pos_x << " {y} - "<< target.pos_y <<  " heuristic |:> " << c_case.heuristic  << "  size open  : " << this->open_list.size() << "  size close  : " << this->close_list.size() << std::endl;
}

void						A_star::get_adjacent(Module_h c_case, Module_h &target, int x, int y, int p)
{
	if (this->map->getCase(x, y) != NULL && this->close_list.count(std::make_pair(x, y)) == 0)
		this->get_heuristic(y, x, target, p);
}

// ###############################################################
