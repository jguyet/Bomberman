#ifndef PLAYER_HPP
# define PLAYER_HPP

#include "All.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Player
{
	public:

		Player(int id, int socket, int udpPort);
		Player( Player const & src );
		virtual ~Player();

		Player &							operator=( Player const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Player const & i);
		int 		getId();
		void		setPosition(float x, float y, float z);


		void				setAddr(int socket, int udpPort);
		struct sockaddr_in	&getAddr();
		struct sockaddr_in	addr;
		int 				id;
		float				x;
		float				y;
		float				z;
		bool				alive;
};

#endif
