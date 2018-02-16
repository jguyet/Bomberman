#include "Socket.hpp"

Socket::Socket ()
{
	return ;
}

Socket::Socket ( Socket const & src )
{
	*this = src;
}

Socket &				Socket::operator=( Socket const & rhs )
{
	return (*this);
}

Socket::~Socket ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Socket const & i)
{
	
	return (o);
}
