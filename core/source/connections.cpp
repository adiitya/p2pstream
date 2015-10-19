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

void Connection::sendData(Data& data, bool block)
{
	int flag = (!block)? MSG_DONTWAIT : 0;

	int len = CHUNK_SIZE;
	char* buffer = new char[len];
	std::cout<<"Sending Data"<<std::endl;
	while(!data.finish())	
	{
		memset(buffer, 0, len);

		int sendLen = data.readData((void*)buffer, len);
		int tmp;
		if((tmp = send(socketId, buffer, sendLen, flag)) != sendLen)
		{	
			std::cout<<tmp<<std::endl;
			delete[] buffer;
			throw std::runtime_error("Connection::sendData: Cannot send data");
		}
	}
	std::cout<<"Data Sent"<<std::endl;
	delete[] buffer;
}


void Connection::receiveData(Data& data, bool block)
{
	int flag = (!block)? MSG_DONTWAIT : 0;
	
	int len = CHUNK_SIZE;

	char* buffer = new char[len];
	std::cout<<"Receiving data :" <<std::endl;
	memset(buffer, 0, len);
	int bytes;

	while((bytes = recv(socketId, buffer, len, flag)) > 0)

	{
	  	data.writeData((void*)buffer, bytes);
	  	std::cout<<buffer<<std::endl;
	  	memset(buffer, 0, len);
	}

	if(block && bytes < 0)
		throw std::runtime_error("Connection::receiveData: Failed to receive bytes from server");

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
