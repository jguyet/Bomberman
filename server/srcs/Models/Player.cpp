#include "Models/Player.hpp"

Player::Player (int id)
{
	this->id = id;
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

int 		Player::getId()
{
	return this->id;
}
