#ifndef SERVERLISTMESSAGE_HPP
# define SERVERLISTMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"
#include "objs/ServerObject.hpp"

#define SERVERS_LEN 4

class ServerListMessage : public IMessage
{
	public:
		static constexpr int ID = 1;

		ServerListMessage(ServerObject servers[SERVERS_LEN]);
		ServerListMessage( ServerListMessage const & src );
		virtual ~ServerListMessage();

		ServerListMessage &							operator=( ServerListMessage const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, ServerListMessage const & i);

		ServerObject servers[SERVERS_LEN];
};


#endif
