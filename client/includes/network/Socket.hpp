#ifndef SOCKET_HPP
# define SOCKET_HPP

class Socket
{
	public:
	
		Socket();
		Socket( Socket const & src );
		virtual ~Socket();

		Socket &							operator=( Socket const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Socket const & i);

	
};

#endif
