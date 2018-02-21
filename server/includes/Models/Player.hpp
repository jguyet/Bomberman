#ifndef PLAYER_HPP
# define PLAYER_HPP

#include "All.hpp"

class Player
{
	public:

		Player(int id);
		Player( Player const & src );
		virtual ~Player();

		Player &							operator=( Player const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Player const & i);
		int 		getId();
	private:
		int 		id;
};

#endif
