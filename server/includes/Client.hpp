#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "All.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Handler.hpp"
#include "Processor.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF_SIZE 1024
class Server;
class Client
{
	public:

		Client(SOCK sock, struct sockaddr_in &in, Server*);
		Client( Client const & src );
		virtual ~Client();

		std::string							getAddress();
		static void							clientThread(Client *client);
		Client &							operator=( Client const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Client const & i);
		SOCK								getSocket();

		Player					*player;
		Server					*server;
		Handler					*messageHandler;
		int 					fd;
		std::string				address;
		struct sockaddr_in		in;
		fd_set					rdfs;
};

#endif
