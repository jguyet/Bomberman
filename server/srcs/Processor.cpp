#include "Processor.hpp"
#include "Server.hpp"

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
	DataManager	*manager = DataManager::Instance();

	manager->updatePos(position);
	Packet packet(new PlayerPositionMessage(position));
	for (int i = 0; i < manager->server->clients.size(); i++)
	{
		if (manager->server->clients[i]->player) {
				packet.sendPacket(manager->server->clients[i]->getSocket());
			}
	}
	// printf("Player id %d (%f, %f, %f)\n", position.playerId, position.x, position.y, position.z);
}

void Processor::NewPlayerMessageHandler(SOCK socket, NewPlayerMessage *message)
{
	DataManager	*manager = DataManager::Instance();
	PlayerPositionObject position = message->position;

	manager->addNewPlayer(socket, position);
}
