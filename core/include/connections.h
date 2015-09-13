#ifndef CONNECTION_H
#define CONNECTION_H


#include <cstdio>
#include <string>

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
public:	
	Connection();
	Connection(int sock);
	Connection(std::string ip, int port);

	std::string getIp();
	int getPort();

	void sendData(const void* data, int len);
	int receiveData(void* buffer, int len);

	void close();

private:
	enum CONN_TYPE {SERVER_CONN, CLIENT_CONN};
	
	int socketId;
	int port;
	std::string ip;
	CONN_TYPE type;
	struct sockaddr_in socketAddr;
};


#endif /* CONNECTION_H */