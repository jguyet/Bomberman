#ifndef PACKET_HPP
# define PACKET_HPP

#include "All.hpp"
#include "IMessage.hpp"
#include "Message.hpp"
#define t_byte char

class Packet
{
	public:

		Packet(IMessage *message);
		Packet( Packet const & src );
		virtual ~Packet();

		Packet &							operator=( Packet const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Packet const & i);

	private:
		t_byte *bytes;
};

#endif
