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

void Client::sendData(const Data data)
{
	connection->sendData(&data);
}

void Client::receiveData()
{
	connection->receiveData();
}

void Client::closeConnection()
{
	connection->close();
}