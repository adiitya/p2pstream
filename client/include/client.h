#ifndef CLIENT_H
#define CLIENT_H


#include <connections.h>
#include <string>

class Client
{
public:
	//Client(std::string ip, int port);
	~Client();
	void createConnection(std::string ip, int port);
	void sendData(const void* data, int len);
	void receiveData(void* data, int len);
	void closeConnection();

private:
	Connection* connection;
};


#endif /* CLIENT_H */