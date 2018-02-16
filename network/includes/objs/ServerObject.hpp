#ifndef SERVER_OBJECT_HPP
# define SERVER_OBJECT_HPP

#include "All.hpp"
#include "enums/ServerType.hpp"
class ServerObject
{
	public:
		ServerObject();
		ServerObject(int server_id, ServerType server_type, bool available);
		ServerObject( ServerObject const & src );
		virtual ~ServerObject();

		ServerObject &							operator=( ServerObject const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, ServerObject const & i);
		bool		available;
		int			id;
		ServerType	type;

};

#endif
