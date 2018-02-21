#include "messages/ServerListMessage.hpp"

ServerListMessage::ServerListMessage(ServerObject servers[SERVERS_LEN]) : IMessage(ServerListMessage::ID, sizeof(IMessage) + sizeof(ServerListMessage))
{
	for (int i = 0; i < SERVERS_LEN; i++)
	{
		this->servers[i] = servers[i];
	}
}

ServerListMessage::ServerListMessage ( ServerListMessage const & src )
{
	*this = src;
}

ServerListMessage &				ServerListMessage::operator=( ServerListMessage const & rhs )
{
	return (*this);
}

ServerListMessage::~ServerListMessage ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, ServerListMessage const & i)
{

	return (o);
}
