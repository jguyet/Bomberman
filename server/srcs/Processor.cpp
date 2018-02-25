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
}

void Processor::NewPlayerMessageHandler(SOCK socket, NewPlayerMessage *message)
{
	DataManager	*manager = DataManager::Instance();
	PlayerPositionObject position = message->position;

	manager->addNewPlayer(socket, position);
}

void Processor::ActionMessageHandler(SOCK, ActionMessage *message)
{
	DataManager	*manager = DataManager::Instance();
	Packet packet(new ActionMessage(message->action, message->byPlayer));
	for (int i = 0 ; i < manager->server->clients.size(); i++) {
		Player *player = manager->server->clients[i]->player;
		if (player != NULL) {
			packet.sendPacket(manager->server->clients[i]->getSocket());
		}
	}
}
