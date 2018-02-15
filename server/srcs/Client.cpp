#include "Client.hpp"
#include "Server.hpp"

Client::Client (SOCK sock, struct sockaddr_in &in, Server *server) : fd(sock), in(in), address(inet_ntoa(in.sin_addr)), server(server)
{
	std::cout << "Hello, i'm from " << this->address << std::endl;

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
	std::cout << "Qui sont ces mega putes ?" << std::endl;
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
