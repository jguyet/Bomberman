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
	if (!(bytes = (t_byte*)malloc(sizeof(t_byte) * message->packet_len))) {
		return NULL;
	}
	memcpy((void*)bytes, (void*)message, message->packet_len);
	return (bytes);
}

int Packet::sendPacket(SOCK socket)
{
	return (send(socket, (void*)this->getMessageRaw(), message->packet_len, 0));
}

int Packet::sendUdpPacket(SOCK socket, struct sockaddr_in addr)
{
	return (sendto(socket, (void*)this->getMessageRaw(), message->packet_len, 0, (struct sockaddr*)&addr, sizeof(addr)));
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
	delete this->message;
}

std::ostream &				operator<<(std::ostream & o, Packet const & i)
{

	return (o);
}
