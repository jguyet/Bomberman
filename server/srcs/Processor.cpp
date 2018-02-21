#include "Processor.hpp"

Processor::Processor ()
{
	return;
}

int *Processor::getMessageId(int id)
{
	int *new_id = NULL;

	if (!(new_id = (int*)malloc(sizeof(int))))
		return (NULL);
	*new_id = id;
	return new_id;
}

Processor::Processor ( Processor const & src )
{
	*this = src;
}

Processor &				Processor::operator=( Processor const & rhs )
{
	return (*this);
}

Processor::~Processor ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Processor const & i)
{

	return (o);
}


void Processor::PlayerPositionMessageHandler(SOCK socket, PlayerPositionMessage *message)
{
	PlayerPositionObject position = message->playerPosition;
	printf("Player id %d (%f, %f, %f)\n", position.playerId, position.x, position.y, position.z);
}
