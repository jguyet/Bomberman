#ifndef PACKET_HPP
# define PACKET_HPP

#include "All.hpp"
#include "IMessage.hpp"
#define t_byte	char
#define SOCK	int

class Packet
{
	public:

		Packet(IMessage *message);
		Packet( Packet const & src );
		virtual ~Packet();
		int			sendPacket(SOCK);
		t_byte		*getMessageRaw();
		IMessage	*getBaseMessage();

		Packet &							operator=( Packet const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Packet const & i);

	private:
		IMessage	*message;
		t_byte		*bytes;
};

#endif
