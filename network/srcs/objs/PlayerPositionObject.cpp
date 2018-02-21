#include "objs/PlayerPositionObject.hpp"

PlayerPositionObject::PlayerPositionObject ()
{

}

PlayerPositionObject::PlayerPositionObject (int playerId, float x, float y, float z)
{
	this->playerId = playerId;
	this->x = x;
	this->y = y;
	this->z = z;
}

PlayerPositionObject::PlayerPositionObject ( PlayerPositionObject const & src )
{
	*this = src;
}

PlayerPositionObject &				PlayerPositionObject::operator=( PlayerPositionObject const & rhs )
{
	this->playerId	= rhs.playerId;
	this->x			= rhs.x;
	this->y 		= rhs.y;
	this->z 		= rhs.z;

	return (*this);
}

PlayerPositionObject::~PlayerPositionObject ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, PlayerPositionObject const & i)
{

	return (o);
}
