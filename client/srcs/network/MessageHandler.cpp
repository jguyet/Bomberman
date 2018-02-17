#include "network/MessageHandler.hpp"

MessageHandler::MessageHandler ()
{
	return ;
}

MessageHandler::MessageHandler ( MessageHandler const & src )
{
	*this = src;
}

MessageHandler &				MessageHandler::operator=( MessageHandler const & rhs )
{
	return (*this);
}

MessageHandler::~MessageHandler ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, MessageHandler const & i)
{

	return (o);
}

void MessageHandler::ServerListMessageHandler(SOCK socket, ServerListMessage *message)
{
	for (int i = 0; i < SERVERS_LEN; i++)
	{
	    std::cout << "Server id: " << std::to_string(message->servers[i].id);
	    if (message->servers[i].type == ServerType::TYPE_1V1) {
	  	  std::cout << ", type: 1v1";
	    }
	    if (message->servers[i].type == ServerType::TYPE_2V2) {
	  	  std::cout << ", type: 2v2";
	    }
	    if (message->servers[i].type == ServerType::TYPE_4V4) {
	  	  std::cout << ", type: 4v4";
	    }
	    if (message->servers[i].type == ServerType::TYPE_FFA) {
	  	  std::cout << ", type: ffa";
	    }
	    std::cout << ", available: " << std::to_string(message->servers[i].available) << std::endl;
	}
}

void MessageHandler::MapSelectMessageHandler(SOCK socket, MapSelectMessage *message)
{
	printf("Please select the map %s\n", message->name.c_str());
	// BombermanClient::instance->current_scene = new GameScene();
}
