#include "Client.hpp"
#include "Server.hpp"

#include "Packet.hpp"
#include "messages/ServerListMessage.hpp"
#include "messages/MapSelectMessage.hpp"
#include "messages/PlayerPositionMessage.hpp"
#include "messages/NewPlayerMessage.hpp"
#include "messages/ActionMessage.hpp"
#include "enums/ServerType.hpp"
#include "objs/ServerObject.hpp"
#include <unistd.h>

Client::Client (SOCK sock, struct sockaddr_in &in, Server *server) : fd(sock), in(in), address(inet_ntoa(in.sin_addr)), server(server)
{
	// ServerObject servers[SERVERS_LEN] = {
	// 	ServerObject(1, ServerType::TYPE_1V1, true),
	// 	ServerObject(2, ServerType::TYPE_2V2, true),
	// 	ServerObject(3, ServerType::TYPE_4V4, true),
	// 	ServerObject(4, ServerType::TYPE_FFA, true)
	//  };
    //
	// Packet *packet = new Packet(new ServerListMessage(servers));
	// packet->sendPacket(sock);

	this->player = NULL;
	this->messageHandler = new Handler(sock,
		Processor::getMessageId(PlayerPositionMessage::ID), &Processor::PlayerPositionMessageHandler,
		Processor::getMessageId(NewPlayerMessage::ID), &Processor::NewPlayerMessageHandler,
		Processor::getMessageId(ActionMessage::ID), &Processor::ActionMessageHandler,
		END_OF_HANDLER);

	Packet mapPacket = Packet(new MapSelectMessage("map_01"));
	mapPacket.sendPacket(sock);

	fcntl(this->fd, F_SETFL, 0 | O_NONBLOCK);

	std::thread thread(Client::clientThread, this);
	thread.detach();
}

Client::Client ( Client const & src )
{
	*this = src;
}

void Client::clientThread(Client *client)
{
	int				res;
	char			buff[BUFF_SIZE];
	struct timeval	tv;
	DataManager		*manager = DataManager::Instance();

	tv.tv_sec = 0;
	tv.tv_usec = 10;
	memset((char*)&buff, 0, (BUFF_SIZE - 1));
	while (42)
	{
		FD_ZERO(&client->rdfs);
		FD_SET(client->fd, &client->rdfs);
		if (select(client->fd + 1, &client->rdfs, NULL, NULL, &tv) == -1) {
			std::cerr << "An error occured " << strerror(errno) << std::endl;
		  	exit(errno);
		}
		if (FD_ISSET(client->fd, &client->rdfs)) {
			if ((res = recv(client->fd, buff, (BUFF_SIZE - 1), 0)) > 0) {
				client->messageHandler->handleMessage((IMessage*)&buff);
				memset((char*)&buff, 0, (BUFF_SIZE - 1));
			} else {
				client->server->removeClient(client);
				break;
			}
		}
	}
}

SOCK Client::getSocket()
{
	return this->fd;
}

Client &				Client::operator=( Client const & rhs )
{
	return (*this);
}

Client::~Client ()
{
	delete this->messageHandler;
}

std::ostream &				operator<<(std::ostream & o, Client const & i)
{
	return (o);
}
