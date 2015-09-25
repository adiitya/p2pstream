#ifndef SERVER_H
#define SERVER_H
#define MAXPENDING 5 //Maximum connection from clients at a time

#include <connections.h>
#include <string>

class Server
{
public:
	~Server();
	
	void startListening(int port, std::string serverIP);
	void respondToClient(int clientsock);
	void close();
private:
	int serversock;

};

#endif /* SERVER_H */