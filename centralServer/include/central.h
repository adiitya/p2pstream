#ifndef CENTRAL_H
#define CENTRAL_H
#define MAXPENDING 5 //Maximum connection from clients at a time
#define mmi std::multimap<std::string, std::string>::iterator

#include <pthread.h>
#include <connections.h>
#include <string>
#include <fstream>
#include <data.h>
#include <iostream>
//#include <../../server/include/server.h>
#include <map>

class CentralServer //: public Server
{
	public:
		CentralServer();
		~CentralServer();
		std::string getIP(std::string);
		void startListening(int port, std::string serverIP);
		static void* respondToClient(void* clientSock);
		void createMap();
		std::multimap<std::string, std::string> fileToIP;
	private:
		int serversock;
};

#endif /* CENTRAL_H */