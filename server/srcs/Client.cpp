#include "Client.hpp"
#include "Server.hpp"

#include "Packet.hpp"
#include "messages/ServerListMessage.hpp"
#include "enums/ServerType.hpp"
#include "objs/ServerObject.hpp"

Client::Client (SOCK sock, struct sockaddr_in &in, Server *server) : fd(sock), in(in), address(inet_ntoa(in.sin_addr)), server(server)
{
	ServerObject servers[SERVERS_LEN] = {
		ServerObject(1, ServerType::TYPE_1V1, true),
		ServerObject(2, ServerType::TYPE_2V2, true),
		ServerObject(3, ServerType::TYPE_4V4, true),
		ServerObject(4, ServerType::TYPE_FFA, true)
	 };

	Packet *packet = new Packet(new ServerListMessage(servers));
	packet->sendPacket(sock);
	// t_byte *raw = packet->getMessageRaw();
    //
	// std::cout << "Packet length: " << std::to_string(packet->getBaseMessage()->packet_len) << std::endl;
    //
	// for (int i = 0;i < packet->getBaseMessage()->packet_len;i++)
	// {
	// 	printf("%x", raw[i]);
	// }
	// printf("\n");
	// ServerListMessage *converted = (ServerListMessage*)raw;
	// printf("%d\n", converted->servers[3].id);

	std::thread thread(Client::clientThread, this);
	thread.detach();
}

Client::Client ( Client const & src )
{
	*this = src;
}

void Client::clientThread(Client *client)
{
	int		res;
	char	buff[BUFF_SIZE];

	memset((char*)&buff, 0, (BUFF_SIZE - 1));
	while ((res = recv(client->fd, buff, (BUFF_SIZE - 1), 0)) > 0)
	{
		std::cout << "Hello: " << buff << std::endl;
		memset((char*)&buff, 0, (BUFF_SIZE - 1));
	}
	client->server->removeClient(client);
}

Client &				Client::operator=( Client const & rhs )
{
	return (*this);
}

Client::~Client ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Client const & i)
{

	return (o);
}
