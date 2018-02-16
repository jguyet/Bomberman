#include "objs/ServerObject.hpp"

ServerObject::ServerObject()
{

}

ServerObject::ServerObject (int server_id, ServerType server_type, bool available)
{
	this->id = server_id;
	this->type = server_type;
	this->available = available;
}

ServerObject::ServerObject ( ServerObject const & src )
{
	*this = src;
}

ServerObject &				ServerObject::operator=( ServerObject const & rhs )
{
	this->available = rhs.available;
	this->id = rhs.id;
	this->type = rhs.type;

	return (*this);
}

ServerObject::~ServerObject ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, ServerObject const & i)
{
	return (o);
}
