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

void Processor::ActionMessageHandler(SOCK socket, ActionMessage *message)
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

void Processor::PlayerDeadMessageHandler(SOCK socket, PlayerDeadMessage *message)
{
	DataManager	*manager		= DataManager::Instance();
	Player		*player			= NULL;
	int			player_alive	= 0;
	if ((player = manager->findPlayerById(message->playerId)) != NULL)
	{
		Packet packet(new PlayerDeadMessage(message->playerId));
		for (int i = 0; i < manager->server->clients.size(); i++) {
			Player *p = manager->server->clients[i]->player;
			if (p != NULL) {

				if (p->getId() == message->playerId)
					p->alive = false;
				if (p->alive == true)
					player_alive++;
				packet.sendPacket(manager->server->clients[i]->getSocket());
			}
		}
		if (player_alive == 1) {
			for (int i = 0; i < manager->server->clients.size(); i++) {
				Player *p = manager->server->clients[i]->player;
				if (p != NULL) {

					if (p->alive) {
						Packet packet(new EndOfGameMessage(true));
						packet.sendPacket(manager->server->clients[i]->getSocket());
					}
					else {
						Packet packet(new EndOfGameMessage(false));
						packet.sendPacket(manager->server->clients[i]->getSocket());
					}
					manager->removePlayer(p);
				}
			}
			manager->gameState = false;
		}
	}
}

void Processor::GameStartedMessageHandler(SOCK, GameStartedMessage *message)
{
	DataManager	*manager	= DataManager::Instance();
	manager->gameState		= message->started;

	Packet packet(new GameStartedMessage(message->started));
	for (int i = 0 ; i < manager->server->clients.size(); i++) {
		Player *player = manager->server->clients[i]->player;
		if (player != NULL) {
			packet.sendPacket(manager->server->clients[i]->getSocket());
		}
	}
}
