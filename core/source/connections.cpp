#include <connections.h>


Connection::Connection()
{
	closed = false;
}

Connection::Connection(int sock)
{
	type 		= CONN_TYPE::SERVER_CONN;
	socketId 	= sock;
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
	inet_pton(socketAddr.sin_family, ip.c_str(), &socketAddr.sin_addr.s_addr);
	
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

void Connection::sendData(const void* data, int len)
{
	if(send(socketId, data, len, 0) != len)
	{
		throw std::runtime_error("Connection::sendData: Cannot send data");
	}
}


int Connection::receiveData(void* buffer, int len)
{
	int bytes = recv(socketId, buffer, len, 0);
	if(bytes < 0)
	{
		throw std::runtime_error("Connection::receiveData: Failed to receive bytes from server");
  	}
  	else if(bytes == 0)
  	{
  		throw std::runtime_error("Connection::receiveData: Client has closed connection");
  	}

  	return bytes;
}

void Connection::close()
{
	if(closed)
		return;

	if(::close(socketId) == -1)
		throw std::runtime_error("Connection::close: Cannot close connection");

	closed = true;
}
