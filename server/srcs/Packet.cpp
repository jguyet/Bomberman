#include "Packet.hpp"

Packet::Packet (IMessage *message)
{
	//std::cout << std::to_string(message->packet_len) << std::endl;
}

Packet::Packet ( Packet const & src )
{
	*this = src;
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
