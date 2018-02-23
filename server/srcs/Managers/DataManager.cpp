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

void DataManager::removePlayer(Player *player)
{
	mutex.lock();
	for (int i = 0; i < this->players.size(); i++)
	{
		if (this->players[i] == player) {
			printf("Player id %d disconnected\n", player->getId());
			this->players.erase(this->players.begin() + i);
			delete player;
			break;
		}
	}
	mutex.unlock();
}

void DataManager::updatePlayers(DataManager *instance)
{
	while (42)
	{
		mutex.lock();
		if (instance->playersPos.size() > 0) {
		 	Packet packet(new PlayersPositionMessage(instance->playersPos));
			for (int i = 0; i < instance->server->clients.size(); i++) {
				packet.sendPacket(instance->server->clients[i]->fd);
			}
			instance->playersPos.clear();
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
			packet.sendPacket(client->getSocket());
		}
	}
}

void DataManager::addNewPlayer(SOCK socket, PlayerPositionObject& pos)
{
	mutex.lock();
	int playerId	= this->getNextPlayerId();
	Client	*client	= this->server->getClientBySock(socket);

	if (client) {
		Player *player = new Player(playerId);
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
