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

void Client::sendData(Data& data)
{
	connection->sendData(data);
}

void Client::receiveData(Data& data)
{
	connection->receiveData(data);
	/*Now we can play/stream or write the data received*/
}

void Client::closeConnection()
{
	connection->close();
}