#ifndef SERVER_HPP
# define SERVER_HPP

#include "All.hpp"
#include "Client.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>

class Server
{
	public:

		Server(int listenPort);
		Server( Server const & src );
		virtual ~Server();

		void start();
		void waitClients();
		void removeClient(Client *client);
		Server &							operator=( Server const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Server const & i);

		struct ServerCantCreateSocket : public std::exception {
			virtual const char* what() const throw() {
				return "The server cant create socket";
			}
		};

		struct ServerCantAllowMultipleConnectionOnSocket : public std::exception {
			virtual const char* what() const throw() {
				return "The server cant allow multiple connection on socket";
			}
		};

		struct ServerCantBindSocket : public std::exception {
			virtual const char* what() const throw() {
				return "The server cant bind the socket";
			}
		};

		struct ServerCantListenOnSocket : public std::exception {
			virtual const char* what() const throw() {
				return "The server cant listen on the socket";
			}
		};

		struct ServerCantAcceptSocket : public std::exception {
			virtual const char* what() const throw() {
				return "The server cant accept socket !";
			}
		};

		struct ServerCantSelectOnFd : public std::exception {
			virtual const char* what() const throw() {
				return "The server cant select on clients fd";
			}
		};

	private:
		std::vector<Client*>		clients;

		std::mutex					mutex;
		int							listenPort;
		struct sockaddr_in			in;
		SOCK						sock;
};

#endif
