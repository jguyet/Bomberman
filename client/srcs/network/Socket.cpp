# include "Bomberman.hpp"

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


	//std::cout << "LOL" << std::endl;
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

      /* something from standard input : i.e keyboard */
    /*  if(FD_ISSET(STDIN_FILENO, &this->rdfs))
      {
         fgets(buffer, BUF_SIZE - 1, stdin);
         {
            char *p = NULL;
            p = strstr(buffer, "\n");
            if(p != NULL)
            {
               *p = 0;
            }
            else
            {
               buffer[BUF_SIZE - 1] = 0;
            }
         }
         write_server(sock, buffer);
	 }
      else */
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
		  std::cout << "Buffer IN :" << buffer << std::endl;
      }
}
