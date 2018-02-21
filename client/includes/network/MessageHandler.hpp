#ifndef MESSAGEHANDLER_HPP
# define MESSAGEHANDLER_HPP

#include "Bomberman.hpp"
#include "Handler.hpp"
#include "messages/ServerListMessage.hpp"
#include "messages/MapSelectMessage.hpp"
#include "messages/NewPlayerMessage.hpp"
#include "messages/PlayerPositionMessage.hpp"
#include "managers/ActionQueueManager.hpp"

class MessageHandler
{
	public:

		MessageHandler();
		MessageHandler( MessageHandler const & src );
		virtual ~MessageHandler();

		static void ServerListMessageHandler(SOCK socket, ServerListMessage *message);
		static void MapSelectMessageHandler(SOCK socket, MapSelectMessage *message);
		static void NewPlayerMessageHandler(SOCK socket, NewPlayerMessage *message);
		static void PlayerPositionMessageHandler(SOCK socket, PlayerPositionMessage *message);

		MessageHandler &							operator=( MessageHandler const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, MessageHandler const & i);
};

#endif
