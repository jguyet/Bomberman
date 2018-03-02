# include "Bomberman.hpp"

int *Socket::getId(int id)
{
	int *new_id = NULL;

	if (!(new_id = (int*)malloc(sizeof(int))))
		return (NULL);
	*new_id = id;
	return new_id;
}

bool Socket::listenTcp(struct sockaddr_in &sin)
{
	if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Can't open the TCP socket");
		return false;
	}

	if(connect(this->sock,(struct sockaddr *) &sin, sizeof(struct sockaddr)) == -1) {
		perror("Can't connect to the server");
		return false;
	}
	return true;
}

bool Socket::listenUdp(int playerId)
{
	struct sockaddr_in sin = { 0 };

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(this->basePort + playerId);
	sin.sin_family = AF_INET;

	if ((this->sockUdp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    	perror("Can't open the UDP socket");
		return false;
	}
	if (bind(this->sockUdp, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
		perror("Can't bind UDP socket");
		return false;
	}
	printf("UDP Listening on port %d\n", this->basePort + playerId);
	return true;
}

Socket::Socket (const char *host, int port) : basePort(port), baseHost(host)
{
	struct sockaddr_in sin = { 0 };
	struct hostent *hostinfo = NULL;

	if (std::string(host) == "") {
		return ;
	}
	if ((hostinfo = gethostbyname(host)) == NULL) {
		fprintf (stderr, "Unknown host %s.\n", host);
		return ;
	}
	sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	if (this->listenTcp(sin))
	{
		std::cout << "Successfully connected to " << host << " on port " << std::to_string(port) << std::endl;
		this->state = true;

		this->handler = new Handler(this->sock,
	   	 this->getId(ServerListMessage::ID), &MessageHandler::ServerListMessageHandler,
		 this->getId(MapSelectMessage::ID), &MessageHandler::MapSelectMessageHandler,
		 this->getId(NewPlayerMessage::ID), &MessageHandler::NewPlayerMessageHandler,
		 this->getId(PlayerPositionMessage::ID), &MessageHandler::PlayerPositionMessageHandler,
		 this->getId(PlayersPositionMessage::ID), &MessageHandler::PlayersPositionMessageHandler,
		 this->getId(ActionMessage::ID), &MessageHandler::ActionMessageHandler,
		 this->getId(PlayerDeadMessage::ID), &MessageHandler::PlayerDeadMessageHandler,
		 this->getId(GameStartedMessage::ID), &MessageHandler::GameStartedMessageHandler,
		 	END_OF_HANDLER);

		std::thread thread(Socket::Thread, this);
		thread.detach();
	}
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
	while (socket->state == true)
	{
		FD_ZERO(&socket->rdfs);
		FD_SET(socket->sock, &socket->rdfs);
		FD_SET(socket->sockUdp, &socket->rdfs);

		if (select((socket->sockUdp > 0) ? socket->sockUdp + 1 : socket->sock + 1, &socket->rdfs, NULL, NULL, &tv) == -1) {
			perror("Can't open select");
		}
		if (FD_ISSET(socket->sock, &socket->rdfs)) {
			if ((rcv = recv(socket->sock, buffer, (BUF_SIZE - 1), 0)) > 0) {
				socket->handler->handleMessage((IMessage*)&buffer);
				memset((char*)&buffer, 0, (BUF_SIZE - 1));
			}
		}
		else if (FD_ISSET(socket->sockUdp, &socket->rdfs)) {
			if ((rcv = recv(socket->sockUdp, buffer, (BUF_SIZE - 1), 0)) > 0) {
				socket->handler->handleMessage((IMessage*)&buffer);
				memset((char*)&buffer, 0, (BUF_SIZE - 1));
			}
		}
	}
	delete socket->handler;
	if (socket->sock != 0)
		close(socket->sock);
	if (socket->sockUdp != 0)
		close(socket->sockUdp);
	delete socket;
}


void					Socket::updateMovement(Script *script)
{
	if (!this->state)
		return ;
	glm::vec3	position = script->gameObject->transform.position;
	int			playerId = ((CharacterControllerScript*)script)->getPlayerId();
	PlayerPositionObject positionObject(playerId, position.x, position.y, position.z);

	Packet movementPacket = Packet(new PlayerPositionMessage(positionObject));
	movementPacket.sendPacket(this->sock);
}

void					Socket::newPlayer(float x, float y, float z)
{
	PlayerPositionObject positionObject(-1, x, y, z);

	Packet playerPacket = Packet(new NewPlayerMessage(positionObject, true));
	playerPacket.sendPacket(this->sock);
}

void					Socket::newBonus(float x, float z)
{
	ActionType	type		= ActionType::TYPE_NONE;
	int			rand_nbr 	= 0;
	Random		randomGen;

	rand_nbr = randomGen.getRandom(0, 100);
	if (rand_nbr < 10)
		type = ActionType::TYPE_BONUS_POWER_UP;
	else if (rand_nbr < 20)
		type = ActionType::TYPE_BONUS_SPEED_UP;
	else if (rand_nbr < 30)
		type = ActionType::TYPE_BONUS_BOMB_UP;
	if (type != ActionType::TYPE_NONE) {
		GameObject *object = BombermanClient::getInstance()->getCurrentScene<GameScene>()->current_player;
		if (object) {
			CharacterControllerScript *script = (CharacterControllerScript*)object->GetComponent<Script>();
			ActionObject object(type, x, 0, z);
			Packet packet(new ActionMessage(object, script->getPlayerId()));
			packet.sendPacket(this->sock);
		}
	}
}

void					Socket::playerDead(int playerId)
{
	Packet playerPacket = Packet(new PlayerDeadMessage(playerId));
	playerPacket.sendPacket(this->sock);
}

void					Socket::sendGameStarted()
{
	Packet playerPacket = Packet(new GameStartedMessage(true));
	playerPacket.sendPacket(this->sock);
}

int 					Socket::getSocket()
{
	return this->sock;
}
