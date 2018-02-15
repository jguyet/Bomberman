#ifndef IMESSAGE_HPP
# define IMESSAGE_HPP

#include "All.hpp"
#define t_byte char

class IMessage
{
	public:
		IMessage(int id, int len) { this->packet_id = id, this->packet_len = len; };
		IMessage() { };
		IMessage( IMessage const & src );
		virtual ~IMessage() { };

		IMessage &							operator=( IMessage const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, IMessage const & i);

		int packet_id;
		int packet_len;
};

#endif
