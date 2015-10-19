#ifndef CLIENT_H
#define CLIENT_H


#include <connections.h>
#include <string>

class Client
{
public:
	//Client(std::string ip, int port);
	Client();
	~Client();
	void createConnection(std::string ip, int port);
	void sendData(Data& data, bool block);
	void receiveData(Data& data, bool block);
	void closeConnection();

private:
	Connection* connection;
};


#endif /* CLIENT_H */