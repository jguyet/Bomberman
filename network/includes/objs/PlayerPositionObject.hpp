#ifndef PLAYERPOSITIONOBJECT_HPP
# define PLAYERPOSITIONOBJECT_HPP

#include "All.hpp"
class PlayerPositionObject
{
	public:

		PlayerPositionObject ();
		PlayerPositionObject(int playerId, float x, float y, float z);
		PlayerPositionObject( PlayerPositionObject const & src );
		virtual ~PlayerPositionObject();

		PlayerPositionObject &							operator=( PlayerPositionObject const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, PlayerPositionObject const & i);
		int		playerId;
		float	x;
		float	y;
		float	z;
};

#endif
