#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "Bomberman.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 4096

# include <messages/ServerListMessage.hpp>

class Socket
{
	public:

											Socket(char *host, int port);
											Socket( Socket const & src );
											virtual ~Socket();

		Socket &							operator=( Socket const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Socket const & i);

		void 								do_select();

	private:
		int 	sock = 0;
		bool	state = false;

		fd_set	rdfs;
};

#endif
