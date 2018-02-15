#ifndef SERVERLISTMESSAGE_HPP
# define SERVERLISTMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"

class ServerListMessage : public IMessage
{
	public:

		ServerListMessage();
		ServerListMessage( ServerListMessage const & src );
		virtual ~ServerListMessage();

		ServerListMessage &							operator=( ServerListMessage const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, ServerListMessage const & i);
		std::vector<std::string> servers;
};

#endif
