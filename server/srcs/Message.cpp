#include "Message.hpp"
#include <stdio.h>

Message::Message ()
{
	this->salope = "Bonjour";
	this->Interessant = 123;
	this->packet_id = 1;
	this->packet_len = sizeof(IMessage) + sizeof(Message);

	// char *r = (char*)this;
	// for(int i = 0;i < this->packet_len; i++)
	// {
	// 	printf("%x\n", r[i]);
	// }
	void *lol = malloc(this->packet_len);
	memcpy(lol, (void*)this, this->packet_len);
	std::cout << ((Message*)lol)->salope << ", " << std::to_string(((Message*)lol)->Interessant) << std::endl;
	return ;
}

Message::Message ( Message const & src )
{
	*this = src;
}

Message &				Message::operator=( Message const & rhs )
{
	return (*this);
}

Message::~Message ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Message const & i)
{

	return (o);
}
