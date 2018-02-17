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
#include "Handler.hpp"
# include "messages/ServerListMessage.hpp"
# include "messages/MapSelectMessage.hpp"
# include "enums/ServerType.hpp"
# include "network/MessageHandler.hpp"
# include <thread>

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

		static void							Thread(Socket *socket);
		void 								do_select();
		int									*getId(int id);

	private:
		int		tmp;
		int 	sock = 0;
		bool	state = false;
		fd_set	rdfs;
		Handler	*handler;
};

#endif
