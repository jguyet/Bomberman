# include "Bomberman.hpp"

int *Socket::getId(int id)
{
	int *new_id = NULL;

	if (!(new_id = (int*)malloc(sizeof(int))))
		return (NULL);
	*new_id = id;
	return new_id;
}

Socket::Socket (char *host, int port)
{
	struct hostent *hostinfo = NULL;
	struct sockaddr_in sin = { 0 };

	if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket()");
		exit(errno);
	}
	if ((hostinfo = gethostbyname(host)) == NULL) {
		fprintf (stderr, "Unknown host %s.\n", host);
		exit(EXIT_FAILURE);
	}
	sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	if(connect(this->sock,(struct sockaddr *) &sin, sizeof(struct sockaddr)) == -1) {
		perror("connect()");
		exit(errno);
	}

	std::cout << "Connected to the server" << std::endl;
	this->state = true;

	this->handler = new Handler(this->sock,
   	 this->getId(ServerListMessage::ID), &MessageHandler::ServerListMessageHandler,
	 this->getId(MapSelectMessage::ID), &MessageHandler::MapSelectMessageHandler, NULL);

	std::thread thread(Socket::Thread, this);
	thread.detach();

	// fcntl(this->sock, F_SETFL, 0 | O_NONBLOCK);
	// this->do_select();
}

Socket::Socket ( Socket const & src )
{
	*this = src;
}

Socket &				Socket::operator=( Socket const & rhs )
{
	return (*this);
}

Socket::~Socket ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Socket const & i)
{
	return (o);
}

void						Socket::Thread(Socket *socket)
{
	struct timeval		tv;
	std::string			types[] = { "1v1", "2v2", "4v4", "ffa" };
	char				buffer[BUF_SIZE];
	int					rcv = 0;

	tv.tv_sec = 0;
	tv.tv_usec = 10;
	if (socket->state != true) {
		std::cout << "Not connected" << std::endl;
		return;
	}
	memset((char*)&buffer, 0, (BUF_SIZE - 1));
	while ((rcv = recv(socket->sock, buffer, (BUF_SIZE - 1), 0)) > 0)
	{
		socket->handler->handleMessage((IMessage*)&buffer);
		memset((char*)&buffer, 0, (BUF_SIZE - 1));
	}
}

// void 						Socket::do_select(void)
// {
//
// 	struct timeval tv;
// 	tv.tv_sec = 0;
// 	tv.tv_usec = 10;
// 	std::string types[] = { "1v1", "2v2","4v4","ffa" };
//
// 	if (this->state != true)
// 	{
// 		std::cout << "Not connected" << std::endl;
// 		return;
// 	}
//
// 	FD_ZERO(&this->rdfs);
//
// 	FD_SET(this->sock, &this->rdfs);
//
// 	if(select(this->sock + 1, &this->rdfs, NULL, NULL, &tv) == -1)
// 	{
// 		perror("select()");
// 		exit(errno);
// 	}
//
// 	if(FD_ISSET(this->sock, &this->rdfs))
// 	{
// 		int n = 0;
// 		char buffer[BUF_SIZE];
// 		if((n = recv(this->sock, buffer, BUF_SIZE - 1, 0)) < 0)
// 		{
// 		perror("recv()");
// 		exit(errno);
// 		}
// 		buffer[n] = 0;
// 		this->handler->handleMessage((IMessage*)&buffer);
// 	}
// }
