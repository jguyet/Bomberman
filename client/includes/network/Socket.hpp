#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "Bomberman.hpp"

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <thread>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "Handler.hpp"
# include "messages/ServerListMessage.hpp"
# include "messages/MapSelectMessage.hpp"
# include "messages/ServerListMessage.hpp"
# include "enums/ServerType.hpp"
# include "network/MessageHandler.hpp"
# include "messages/PlayerPositionMessage.hpp"
# include "messages/PlayersPositionMessage.hpp"
# include "messages/NewPlayerMessage.hpp"
# include "Packet.hpp"
#define BUF_SIZE 16000

class Script;
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
		void								updateMovement(Script*);
		void								newPlayer(float x, float y, float z);

	private:
		int		tmp;
		int 	sock = 0;
		bool	state = false;
		fd_set	rdfs;
		Handler	*handler;
};

#endif
