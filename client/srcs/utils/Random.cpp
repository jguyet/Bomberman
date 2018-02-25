#include "utils/Random.hpp"

Random::Random ()
{
	srand(time(NULL));
}

Random::Random ( Random const & src )
{
	*this = src;
}

Random &				Random::operator=( Random const & rhs )
{
	return (*this);
}

Random::~Random ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Random const & i)
{

	return (o);
}


int Random::getRandom(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}
