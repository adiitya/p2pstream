#ifndef SERVER_H
#define SERVER_H
#define MAXPENDING 5 //Maximum connection from clients at a time

#include <pthread.h>
#include <connections.h>
#include <string>
#include <data.h>
#include <vector>

class Server
{
public:
	~Server();
	Server();

	void startListening(int port, std::string serverIP);
	static void* respondToClient(void* clientsock);
	void close();
private:
	int serversock;
	//std::vector<pthread_t*> connThreads;

};

#endif /* SERVER_H */