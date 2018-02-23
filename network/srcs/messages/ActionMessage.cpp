#include "messages/ActionMessage.hpp"

ActionMessage::ActionMessage (ActionObject &object, int byPlayer) : IMessage(ActionMessage::ID, sizeof(IMessage) + sizeof(ActionMessage))
{
	this->action = object;
	this->byPlayer = byPlayer;
}

ActionMessage::ActionMessage ( ActionMessage const & src )
{
	*this = src;
}

ActionMessage &				ActionMessage::operator=( ActionMessage const & rhs )
{
	return (*this);
}

ActionMessage::~ActionMessage ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, ActionMessage const & i)
{

	return (o);
}
