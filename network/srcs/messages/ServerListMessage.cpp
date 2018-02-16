#include "messages/ServerListMessage.hpp"

ServerListMessage::ServerListMessage(ServerObject servers[SERVERS_LEN]) : IMessage(1, sizeof(IMessage) + sizeof(ServerListMessage))
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

//
//
// opensock();
// processor = new Processor(&handlerListMessage, ServerListMessage::id,
// 			  &handlerUpdateMap, UpdateMapMessage::id, END);
//
// onconnected()
// {
// 	read()
// 	{
// 		packet = new packet((IMessage)*raw);
// 		processor->handle(packet->getMessage()->packet_id);
// 	}
// }
