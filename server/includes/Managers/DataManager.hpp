#ifndef DATAMANAGER_HPP
# define DATAMANAGER_HPP

#include <mutex>
#include <atomic>

#include "All.hpp"
#include "Models/Player.hpp"
#include "objs/PlayerPositionObject.hpp"
#include "Packet.hpp"
#include "messages/PlayersPositionMessage.hpp"

class Client;
class Server;
class DataManager
{
	public:
		static DataManager		*Instance();

		DataManager();
		DataManager( DataManager const & src );
		virtual ~DataManager();

		DataManager &							operator=( DataManager const & rhs );
		friend std::ostream &					operator<<(std::ostream & o, DataManager const & i);

		void									addNewPlayer(SOCK socket, PlayerPositionObject&);
		void									removePlayer(Player*);
		int										getNextPlayerId();
		Player									*findPlayerById(int playerId);
		void									updatePos(PlayerPositionObject&);
		void									sendPlayers(Client *client);
		void									disconnectClients();
		static void								updatePlayers(DataManager *manager);

		bool										gameState;
		static std::atomic<DataManager*>			pInstance;
		static std::mutex							mutex;
		std::vector<Player*>						players;
		Server										*server;
		std::vector<PlayerPositionObject>			playersPos;
};

#endif
