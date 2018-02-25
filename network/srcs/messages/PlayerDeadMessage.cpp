#include "messages/PlayerDeadMessage.hpp"

PlayerDeadMessage::PlayerDeadMessage (int playerId) : IMessage(PlayerDeadMessage::ID, sizeof(IMessage) + sizeof(PlayerDeadMessage))
{
	this->playerId = playerId;
}

PlayerDeadMessage::PlayerDeadMessage ( PlayerDeadMessage const & src )
{
	*this = src;
}

PlayerDeadMessage &				PlayerDeadMessage::operator=( PlayerDeadMessage const & rhs )
{
	return (*this);
}

PlayerDeadMessage::~PlayerDeadMessage ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, PlayerDeadMessage const & i)
{
	return (o);
}
