#include "Server.hpp"

Server::Server (int listenPort) : listenPort(listenPort)
{

}

Server::Server ( Server const & src )
{
	*this = src;
}

void Server::removeClient(Client *client)
{
	this->mutex.lock();
	for (int i = 0; i < this->clients.size(); i++)
	{
		if (this->clients[i] == client) {
			delete client;
			this->clients.erase(this->clients.begin() + i);
			break;
		}
	}
	this->mutex.unlock();
}

void Server::waitClients()
{
	SOCK 					fd		= 0;
	socklen_t				length	= sizeof(in);
	SOCK					max_fd	= 0;
	struct sockaddr_in		in;

	while (42)
	{
		if ((fd = accept(this->sock, (struct sockaddr*)&in, &length)) == -1)
			throw ServerCantAcceptSocket();
		this->clients.push_back(new Client(fd, in, this));
	}
}

void Server::start()
{
	int opt = true;
	if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw ServerCantCreateSocket();
	this->in.sin_family = AF_INET;
	this->in.sin_addr.s_addr = INADDR_ANY;
	this->in.sin_port = htons(this->listenPort);

	if (setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0)
	    throw ServerCantBindSocket();
	if ((bind(this->sock, (struct sockaddr *)&this->in, sizeof(this->in))) < 0)
		throw ServerCantBindSocket();
	if ((listen(this->sock, 3)) == -1)
		throw ServerCantListenOnSocket();

	std::cout << "Bomber server listening on port " << std::to_string(this->listenPort) << std::endl;
	this->waitClients();
}

Server &				Server::operator=( Server const & rhs )
{
	return (*this);
}

Server::~Server ()
{

}

std::ostream &				operator<<(std::ostream & o, Server const & i)
{

	return (o);
}
