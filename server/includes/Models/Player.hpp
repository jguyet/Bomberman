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
		void		setPosition(float x, float y, float z);
		int 		id;
		float		x;
		float		y;
		float		z;
};

#endif
