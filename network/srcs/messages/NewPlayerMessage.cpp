#include "messages/NewPlayerMessage.hpp"

NewPlayerMessage::NewPlayerMessage (PlayerPositionObject &playerPosition, bool owner) : IMessage(NewPlayerMessage::ID, sizeof(IMessage) + sizeof(NewPlayerMessage))
{
	this->position = playerPosition;
	this->owner = owner;
}

NewPlayerMessage::NewPlayerMessage ( NewPlayerMessage const & src )
{
	*this = src;
}

NewPlayerMessage &				NewPlayerMessage::operator=( NewPlayerMessage const & rhs )
{
	return (*this);
}

NewPlayerMessage::~NewPlayerMessage ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, NewPlayerMessage const & i)
{

	return (o);
}
