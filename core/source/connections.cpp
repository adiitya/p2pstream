#include <connections.h>
#include <iostream>

Connection::Connection()
{
	// socket not opened
	closed = true;
}

Connection::Connection(int sock)
{
	type 		= CONN_TYPE::SERVER_CONN;
	socketId 	= sock;

	// opened by OS
	closed 		= false;
}

Connection::~Connection()
{
	close();
}

Connection::Connection(std::string ip, int port)
{
	type = CONN_TYPE::CLIENT_CONN;

	this->ip = ip;
	this->port = port;
	
	memset(&socketAddr, 0, sizeof(socketAddr));

	socketAddr.sin_family 		= AF_INET;
	socketAddr.sin_port 		= htons(port);
	inet_pton(socketAddr.sin_family, ip.c_str(), &(socketAddr.sin_addr.s_addr));
	
	//Creating socket
	if ((socketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
	{
		throw std::runtime_error("Connection::Connection: Failed to create socket");
	}
	
	//Connecting to created socket
	if(connect(socketId, (struct sockaddr*) &socketAddr, sizeof(socketAddr)) < 0) 
	{
		throw std::runtime_error("Connection::Connection: Unable to connect");
	}

	// manually opened
	closed = false;
}


std::string Connection::getIp()
{
	return (type == CONN_TYPE::CLIENT_CONN)? ip : "";
}

int Connection::getPort()
{
	return (type == CONN_TYPE::CLIENT_CONN)? port : -1;
}

void Connection::sendData(Data& data)
{
	int len = data.getChunkSize();
	char* buffer = new char[len];

	while(!data.finish())
	{
		memset(buffer, 0, len);

		int sendLen = data.readData((void*)buffer, len);
		if(send(socketId, buffer, sendLen, 0) != sendLen)
		{
			delete[] buffer;
			throw std::runtime_error("Connection::sendData: Cannot send data");
		}
	}

	delete[] buffer;
}


void Connection::receiveData(Data& data)
{
	int len = data.getChunkSize();
	char* buffer = new char[len];

	while(!data.finish())
	{
		memset(buffer, 0, len);

		int bytes = recv(socketId, buffer, len, 0);
		if(bytes < 0)
		{
			delete[] buffer;
			throw std::runtime_error("Connection::receiveData: Failed to receive bytes from server");
	  	}
	  	else if(bytes == 0)
	  	{
	  		delete[] buffer;
	  		throw std::runtime_error("Connection::receiveData: Client has closed connection");
	  	}

	  	data.writeData((void*)buffer, bytes);
	}

	delete[] buffer;
}

void Connection::close()
{
	if(closed)
		return;

	if(::close(socketId) == -1)
		throw std::runtime_error("Connection::close: Cannot close connection");

	closed = true;
}
