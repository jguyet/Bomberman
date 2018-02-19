#ifndef ACTIONQUEUE_HPP
# define ACTIONQUEUE_HPP

#include "Bomberman.hpp"
#include "IMessage.hpp"

class ActionQueue
{
	public:

		ActionQueue(int messageId, IMessage *message);
		ActionQueue( ActionQueue const & src );
		virtual ~ActionQueue();

		ActionQueue &							operator=( ActionQueue const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, ActionQueue const & i);
		int			messageId;
		t_byte		*message;

};

#endif
