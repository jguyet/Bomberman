# include "Bomberman.hpp"
# include "messages/ServerListMessage.hpp"
# include "enums/ServerType.hpp"

Socket::Socket (char *host, int port)
{

	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if(this->sock == -1)
	{
		perror("socket()");
		exit(errno);
	}


	struct hostent *hostinfo = NULL;

	struct sockaddr_in sin = { 0 };


	hostinfo = gethostbyname(host);
	if (hostinfo == NULL)
	{
		fprintf (stderr, "Unknown host %s.\n", host);
		exit(EXIT_FAILURE);
	}

	sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	if(connect(sock,(struct sockaddr *) &sin, sizeof(struct sockaddr)) == -1)
	{
		perror("connect()");
		exit(errno);
	}


	fcntl(this->sock, F_SETFL, 0 | O_NONBLOCK);

	std::cout << "Connection to server OK ! " << std::endl;
	this->state = true;

	return ;
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

void 						Socket::do_select(void)
{

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 10;
	std::string types[] = { "1v1", "2v2","4v4","ffa" };

	if (this->state != true)
	{
		std::cout << "Not connect bitch" << std::endl;
		return;
	}

	FD_ZERO(&this->rdfs);

    /* add STDIN_FILENO */
    //FD_SET(STDIN_FILENO, &this->rdfs);

      /* add the socket */
      FD_SET(this->sock, &this->rdfs);

      if(select(this->sock + 1, &this->rdfs, NULL, NULL, &tv) == -1)
      {
         perror("select()");
         exit(errno);
      }

	  if(FD_ISSET(this->sock, &this->rdfs))
      {
		  int n = 0;
		  char buffer[BUF_SIZE];
	      if((n = recv(this->sock, buffer, BUF_SIZE - 1, 0)) < 0)
	      {
	         perror("recv()");
	         exit(errno);
	      }

	      buffer[n] = 0;
		  ServerListMessage *message = (ServerListMessage*)&buffer;
		  std::cout << "Packet id received: " << std::to_string(message->packet_id) << std::endl;
		  std::cout << "Servers :" << std::endl;
		  for (int i = 0; i < SERVERS_LEN; i++)
		  {
			  std::cout << "Server id: " << std::to_string(message->servers[i].id);
			  if (message->servers[i].type == ServerType::TYPE_1V1) {
				  std::cout << ", type: 1v1";
			  }
			  if (message->servers[i].type == ServerType::TYPE_2V2) {
				  std::cout << ", type: 2v2";
			  }
			  if (message->servers[i].type == ServerType::TYPE_4V4) {
				  std::cout << ", type: 4v4";
			  }
			  if (message->servers[i].type == ServerType::TYPE_FFA) {
				  std::cout << ", type: ffa";
			  }
			  std::cout << ", available: " << std::to_string(message->servers[i].available) << std::endl;
		  }
      }
}
