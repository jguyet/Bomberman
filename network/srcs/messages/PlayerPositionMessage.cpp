#include "messages/PlayerPositionMessage.hpp"

PlayerPositionMessage::PlayerPositionMessage (PlayerPositionObject &playerPosition) : IMessage(PlayerPositionMessage::ID, sizeof(IMessage) + sizeof(PlayerPositionMessage))
{
	this->playerPosition = playerPosition;
}

PlayerPositionMessage::PlayerPositionMessage ( PlayerPositionMessage const & src )
{
	*this = src;
}

PlayerPositionMessage &				PlayerPositionMessage::operator=( PlayerPositionMessage const & rhs )
{
	return (*this);
}

PlayerPositionMessage::~PlayerPositionMessage ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, PlayerPositionMessage const & i)
{

	return (o);
}
