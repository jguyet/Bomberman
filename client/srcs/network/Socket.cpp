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
	 this->getId(MapSelectMessage::ID), &MessageHandler::MapSelectMessageHandler, END_OF_HANDLER);

	std::thread thread(Socket::Thread, this);
	thread.detach();
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


void					Socket::updateMovement(Script *script)
{
	glm::vec3	position = script->gameObject->transform.position;
	int			playerId = ((CharacterControllerScript*)script)->getPlayerId();
	PlayerPositionObject positionObject(playerId, position.x, position.y, position.z);

	Packet movementPacket = Packet(new PlayerPositionMessage(positionObject));
	movementPacket.sendPacket(this->sock);
}
