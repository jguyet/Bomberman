#ifndef MESSAGEHANDLER_HPP
# define MESSAGEHANDLER_HPP

#include "Bomberman.hpp"
#include "Handler.hpp"
#include "messages/ServerListMessage.hpp"
#include "messages/MapSelectMessage.hpp"
#include "messages/NewPlayerMessage.hpp"
#include "messages/PlayerPositionMessage.hpp"
#include "messages/PlayersPositionMessage.hpp"
#include "messages/ActionMessage.hpp"
#include "messages/PlayerDeadMessage.hpp"
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
		static void PlayersPositionMessageHandler(SOCK socket, PlayersPositionMessage *message);
		static void ActionMessageHandler(SOCK socket, ActionMessage *message);
		static void PlayerDeadMessageHandler(SOCK socket, PlayerDeadMessage *message);

		MessageHandler &							operator=( MessageHandler const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, MessageHandler const & i);
};

#endif
