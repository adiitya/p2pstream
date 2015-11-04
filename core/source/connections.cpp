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
	std::cout<<"\nSending Data ...\n"<<std::endl;
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
	std::cout<<"Data Sent Successfully!\n"<<std::endl;
	delete[] buffer;
}


void Connection::receiveData(Data& data, bool block)
{
	int flag = (!block)? MSG_DONTWAIT : 0;
	if(!block)sleep(1);
	int len = CHUNK_SIZE;

	char* buffer = new char[len];
	std::cout<<"Receiving data ...\n" <<std::endl;
	memset(buffer, 0, len);
	int bytes;
	int total=0;
	std::cout<<"Amount of data buffered :"<<std::endl;
	while((bytes = recv(socketId, buffer, len, flag)) > 0)
	{
	  	data.writeData((void*)buffer, bytes);
	  	total=total+bytes;
	  	std::cout<<total/(1024*1024)<<" MB"<<"\r";//<<std::endl;
	  	memset(buffer, 0, len);
	}
	std::cout<<"\n"<<std::endl;

	if(block && bytes < 0)
		throw std::runtime_error("Connection::receiveData: Failed to receive data from server");

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
