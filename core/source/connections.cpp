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
	sendHeader(data.getFileName(), data.getFileSize());
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


void Connection::receiveData()
{
	struct MHeader header = receiveHeader();
	Data data("downloads/" + std::string(header.name), CHUNK_SIZE, Data::TYPE::WRITE);

	int len = data.getChunkSize();
	char* buffer = new char[len];
	std::cout<<"Receiving data :" <<std::endl;
	memset(buffer, 0, len);
	int bytes;
	while((bytes = recv(socketId, buffer, len, 0)) > 0)
	{
	  	data.writeData((void*)buffer, bytes);
	  	memset(buffer, 0, len);
	}
	if(bytes < 0)
		throw std::runtime_error("Connection::receiveData: Failed to receive bytes from server");

	delete[] buffer;
}

void Connection::sendHeader(std::string fileName, long long fileSize)
{
	struct MHeader header;
	memcpy(header.name, fileName.c_str(), MAX_FILE_NAME);
	header.length = fileSize;

	if(send(socketId, &header, MAX_HEADER_SIZE, 0) != MAX_HEADER_SIZE)
	{
		throw std::runtime_error("Connection::sendHeader: Cannot send header");
	}
}

struct MHeader Connection::receiveHeader()
{
	struct MHeader header;
	if(recv(socketId, &header, MAX_HEADER_SIZE, 0) < 0)
	{
		throw std::runtime_error("Connection::receiveHeader::Unable to receive header");
	}
	return header;
}

void Connection::close()
{
	if(closed)
		return;

	if(::close(socketId) == -1)
		throw std::runtime_error("Connection::close: Cannot close connection");

	closed = true;
}
