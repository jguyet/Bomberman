#include "models/ActionQueue.hpp"

ActionQueue::ActionQueue (int messageId, IMessage *message)
{
	this->messageId = messageId;
	t_byte *bytes = NULL;
	if (!(bytes = (t_byte*)malloc(sizeof(t_byte) * message->packet_len))) {
		return;
	}
	memcpy((void*)bytes, (void*)message, message->packet_len);
	this->message = bytes;
}

ActionQueue::ActionQueue ( ActionQueue const & src )
{
	*this = src;
}

ActionQueue &				ActionQueue::operator=( ActionQueue const & rhs )
{
	return (*this);
}

ActionQueue::~ActionQueue()
{
	free(this->message);
}

std::ostream &				operator<<(std::ostream & o, ActionQueue const & i)
{
	return (o);
}
