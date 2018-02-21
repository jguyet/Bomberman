#ifndef DATAMANAGER_HPP
# define DATAMANAGER_HPP

#include <mutex>
#include <atomic>

#include "All.hpp"
#include "Models/Player.hpp"
#include "objs/PlayerPositionObject.hpp"
#include "Packet.hpp"

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

		static std::atomic<DataManager*>		pInstance;
		static std::mutex						mutex;
		void									addNewPlayer(SOCK socket, PlayerPositionObject&);
		void									removePlayer(Player*);
		int										getNextPlayerId();

		std::vector<Player*>						players;
		Server										*server;
};

#endif
