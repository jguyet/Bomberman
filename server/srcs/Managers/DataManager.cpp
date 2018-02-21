#include "Managers/DataManager.hpp"
#include "Server.hpp"

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
	for (int i = 0; i < this->players.size(); i++)
	{
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
	}
	mutex.unlock();
}

DataManager::DataManager ()
{
	return ;
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
