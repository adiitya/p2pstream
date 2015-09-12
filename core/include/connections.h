#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

class Connection
{
	enum CONN_TYPE {SERVER_CONN, CLIENT_CONN};
	int sock_fd;
	char *ip;
	int port;
	CONN_TYPE type;
	struct sockaddr_in socketAddr;
	public:	
		Connection(int sock);
		Connection(char* ip, int port);
		~Connection();
		char* getIp();
		int getPort();
		void sendData(char* message);
		int recData(char *buffer, int BUFFSIZE);
};

#endif /* CONNECTION_H */