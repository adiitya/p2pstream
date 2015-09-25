#include <client.h>
#ifdef DEBUG
#include <iostream>
#endif

Client::Client()
{
	connection = NULL;
}

Client::~Client()
{
	delete connection;
}
void Client::createConnection(std::string ip, int port)
{
	connection = new Connection(ip, port);
}

void Client::sendData(const void* data, int len)
{
	connection->sendData(data, len);
}

void Client::receiveData(void* data, int len)
{
	connection->receiveData(data, len);
}

void Client::closeConnection()
{
	connection->close();
}