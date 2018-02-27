#include "messages/GameStartedMessage.hpp"

GameStartedMessage::GameStartedMessage (bool started) : IMessage(GameStartedMessage::ID, sizeof(IMessage) + sizeof(GameStartedMessage))
{
	this->started = started;
}

GameStartedMessage::GameStartedMessage ( GameStartedMessage const & src )
{
	*this = src;
}

GameStartedMessage &				GameStartedMessage::operator=( GameStartedMessage const & rhs )
{
	return (*this);
}

GameStartedMessage::~GameStartedMessage ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, GameStartedMessage const & i)
{

	return (o);
}
