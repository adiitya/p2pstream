#include <client.h>
#include <iostream>

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

void Client::sendData(Data& data, bool block)
{
	connection->sendData(data, block);
}

void Client::receiveData(Data& data, bool block)
{
	connection->receiveData(data, block);
	/*Now we can play/stream or write the data received*/
}

void Client::closeConnection()
{
	connection->close();
}