#include "messages/ServerListMessage.hpp"

ServerListMessage::ServerListMessage() : IMessage(1, sizeof(IMessage) + sizeof(ServerListMessage))
{
	this->servers.push_back("1v1");
	this->servers.push_back("2v2");
	this->servers.push_back("4v4");
	this->servers.push_back("5v5");
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
