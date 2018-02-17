#include "Handler.hpp"
#include "messages/MapSelectMessage.hpp"

Handler::Handler (SOCK socket, ...) : socket(socket)
{
	va_list		args;
	void		*content;
	bool		handler = false;
	int			ID = -1;

	va_start(args, socket);
	while ((content = va_arg(args, void*)) != NULL)
	{
		if (!handler) {
			ID = *(int*)content;
			free(content);
			handler = true;
		} else {
			this->handlers.insert(std::make_pair(ID, content));
			handler = false;
		}
	}
	va_end(args);
}

void Handler::handleMessage(IMessage *message)
{
	void(*exec)(SOCK, IMessage *);
	void *func = this->handlers[message->packet_id];
	if (func != NULL) {
		exec = (void (*)(SOCK, IMessage *))func;
		exec(this->socket, message);
	}
}

Handler::Handler ( Handler const & src )
{
	*this = src;
}

Handler &				Handler::operator=( Handler const & rhs )
{
	return (*this);
}

Handler::~Handler ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Handler const & i)
{
	return (o);
}
