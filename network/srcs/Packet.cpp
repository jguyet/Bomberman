#include "Packet.hpp"

Packet::Packet (IMessage *message)
{
	this->message = message;
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
	t_byte *raw = this->getMessageRaw();

	if (raw == NULL)
		return 0;
	int result = send(socket, (void*)raw, message->packet_len, 0);
	free(raw);
	return (result);
}

int Packet::sendUdpPacket(SOCK socket, struct sockaddr_in addr)
{
	t_byte *raw = this->getMessageRaw();

	if (raw == NULL)
		return 0;
	int result = sendto(socket, (void*)this->getMessageRaw(), message->packet_len, 0, (struct sockaddr*)&addr, sizeof(addr));
	free(raw);
	return (result);
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
