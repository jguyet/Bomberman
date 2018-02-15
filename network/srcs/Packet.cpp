#include "Packet.hpp"

Packet::Packet (IMessage *message) : message(message)
{
	//std::cout << std::to_string(message->packet_len) << std::endl;
}

Packet::Packet ( Packet const & src )
{
	*this = src;
}

t_byte *Packet::getMessageRaw()
{
	if (!(bytes = (t_byte*)malloc(sizeof(char) * message->packet_len))) {
		return NULL;
	}
	memcpy((void*)bytes, (void*)message, message->packet_len);
	return (bytes);
}

IMessage *Packet::getBaseMessage()
{
	return this->message;
}

Packet &				Packet::operator=( Packet const & rhs )
{
	return (*this);
}

Packet::~Packet ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Packet const & i)
{

	return (o);
}
