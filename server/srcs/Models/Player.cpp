#include "Models/Player.hpp"

Player::Player (int id, int socket, int udpPort)
{
	this->id = id;
	this->setAddr(socket, udpPort);
}

Player::Player ( Player const & src )
{
	*this = src;
}

Player &				Player::operator=( Player const & rhs )
{
	return (*this);
}

Player::~Player ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Player const & i)
{

	return (o);
}

void		Player::setAddr(int socket, int udpPort)
{
	socklen_t addr_size = sizeof(struct sockaddr_in);
	getpeername(socket, (struct sockaddr *)&this->addr, &addr_size);
	this->addr.sin_port = htons(udpPort);
}

struct sockaddr_in	&Player::getAddr()
{
	return this->addr;
}

int 		Player::getId()
{
	return this->id;
}

void		Player::setPosition(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
