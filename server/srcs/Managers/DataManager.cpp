#include "Managers/DataManager.hpp"
#include "Server.hpp"
#include <unistd.h>

std::atomic<DataManager*> DataManager::pInstance { nullptr };
std::mutex DataManager::mutex;

DataManager* DataManager::Instance()
{
  if(pInstance == nullptr)
  {
  	std::lock_guard<std::mutex> lock(mutex);
  	if(pInstance == nullptr) {
  		pInstance = new DataManager();
  	}
  }
  return pInstance;
}

int	DataManager::getNextPlayerId()
{
	int id = 0;
	for (int i = 0; i < this->players.size(); i++) {
		id = this->players[i]->getId();
	}
	return id + 1;
}

Player *DataManager::findPlayerById(int playerId)
{
	std::lock_guard<std::mutex> lock(mutex);
	for (int i = 0; i < this->players.size(); i++) {
		if (this->players[i]->getId() == playerId) {
			return this->players[i];
		}
	}
	return NULL;
}

void DataManager::removePlayer(Player *player)
{
	mutex.lock();
	for (int i = 0; i < this->players.size(); i++)
	{
		if (this->players[i] == player) {
			printf("Player id %d dead/disconnected\n", player->getId());
			this->players.erase(this->players.begin() + i);
			delete player;
			break;
		}
	}
	mutex.unlock();
}

void DataManager::disconnectClients()
{
	for (int i = 0; i < instance->server->clients.size(); i++) {
		Client *client = instance->server->clients[i];
		if (client->fd) {
			close(client->fd);
		}
	}
}

void DataManager::updatePlayers(DataManager *instance)
{
	while (42)
	{
		mutex.lock();
		if (instance->playersPos.size() > 0) {
		 	Packet packet(new PlayersPositionMessage(instance->playersPos));
			for (int i = 0; i < instance->server->clients.size(); i++) {
				Player *player = instance->server->clients[i]->player;
				if (player != NULL) {
					packet.sendUdpPacket(instance->server->getUdpSocket(), player->getAddr());
				}
			}
			instance->playersPos.clear();
		}
		if (instance->gameState && players.size() <= 1) {
			instance->disconnectClients();
			instance->gameState = false;
		}
		usleep(50 * 1000);
		mutex.unlock();
	}
}

void DataManager::sendPlayers(Client *client)
{
	for (int i = 0; i < this->players.size(); i++) {
		Player *player = this->players[i];
		if (player != client->player) {
			PlayerPositionObject obj(player->id, player->x, player->y, player->z);
			Packet packet(new NewPlayerMessage(obj, false));
			packet.sendUdpPacket(client->server->getUdpSocket(), client->player->getAddr());
		}
	}
}

void DataManager::addNewPlayer(SOCK socket, PlayerPositionObject& pos)
{
	mutex.lock();
	int playerId	= this->getNextPlayerId();
	Client	*client	= this->server->getClientBySock(socket);

	if (client) {
		Player *player = new Player(playerId, socket, (client->server->listenPort + playerId));
		player->x = pos.x;
		player->y = pos.y;
		player->z = pos.z;
		client->player = player;

		pos.playerId = playerId;
		printf("Received a new player id: %d (%f, %f, %f)\n", playerId, pos.x, pos.y, pos.z);
		this->players.push_back(player);
		NewPlayerMessage *message = new NewPlayerMessage(pos, true);

		Packet playerMessage = Packet(message);
		playerMessage.sendPacket(socket);
		message->owner = false;
		for (int i = 0; i < this->server->clients.size(); i++)
		{
			if (this->server->clients[i]->player &&
				this->server->clients[i]->player != player) {
					playerMessage.sendPacket(this->server->clients[i]->getSocket());
				}
		}
		usleep(500 * 1000);
		this->sendPlayers(client);
	}

	mutex.unlock();
}

void DataManager::updatePos(PlayerPositionObject &pos)
{
	std::lock_guard<std::mutex> lock(mutex);

	for (int i = 0; i < this->server->clients.size(); i++)
	{
		Player *player = this->server->clients[i]->player;
		if (player != NULL && player->id == pos.playerId) {
			player->x = pos.x;
			player->y = pos.y;
			player->z = pos.z;
			this->playersPos.push_back(PlayerPositionObject(player->id, pos.x, pos.y, pos.z));
		}
	}
}

DataManager::DataManager ()
{
	std::thread thread(DataManager::updatePlayers, this);
	thread.detach();
}

DataManager::DataManager ( DataManager const & src )
{
	*this = src;
}

DataManager &				DataManager::operator=( DataManager const & rhs )
{
	return (*this);
}

DataManager::~DataManager ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, DataManager const & i)
{

	return (o);
}
