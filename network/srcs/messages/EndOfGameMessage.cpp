#include "messages/EndOfGameMessage.hpp"

#include "All.hpp"
#include "IMessage.hpp"

EndOfGameMessage::EndOfGameMessage () : IMessage(EndOfGameMessage::ID, sizeof(IMessage) + sizeof(EndOfGameMessage))
{
	return ;
}

EndOfGameMessage::EndOfGameMessage ( EndOfGameMessage const & src )
{
	*this = src;
}

EndOfGameMessage &				EndOfGameMessage::operator=( EndOfGameMessage const & rhs )
{
	return (*this);
}

EndOfGameMessage::~EndOfGameMessage ()
{
	return ;
}

std::ostream &					operator<<(std::ostream & o, EndOfGameMessage const & i)
{

	return (o);
}
