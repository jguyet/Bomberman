#include "messages/EndOfGameMessage.hpp"

#include "All.hpp"
#include "IMessage.hpp"

EndOfGameMessage::EndOfGameMessage (bool is_winner) : IMessage(EndOfGameMessage::ID, sizeof(IMessage) + sizeof(EndOfGameMessage))
{
	this->is_winner = is_winner;
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
