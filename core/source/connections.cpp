#include <connections.h>


Connection::Connection()
{}

Connection::Connection(int sock)
{
	type = CONN_TYPE::SERVER_CONN;
	socketId = sock;
}

Connection::Connection(std::string ip, int port)
{
	type = CONN_TYPE::CLIENT_CONN;
	this->ip = ip;
	this->port = port;
	
	memset(&socketAddr, 0, sizeof(socketAddr));

	socketAddr.sin_family = AF_INET;
	socketAddr.sin_addr.s_addr = inet_addr(ip.c_str());
	socketAddr.sin_port = htons(port);
	
	//Creating socket
	if ((socketId = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
	{
		throw std::runtime_error("Connection::Connection Failed to create socket");
	}

	//Connecting to created socket
	if(connect(socketId, (struct sockaddr *) &socketAddr, sizeof(socketAddr)) < 0) 
	{
		throw std::runtime_error("Connection::Connection Unable to connect");
	}
}

std::string Connection::getIp()
{
	return (type == CLIENT_CONN)? ip : "";
}

int Connection::getPort()
{
	return (type == CLIENT_CONN)? port : -1;
}

void Connection::sendData(const void* data, int len)
{
	if(send(socketId, data, len, 0) != len)
	{
		throw std::runtime_error("Connection::sendData Mismatch in number of sent bytes");
	}
}

int Connection::receiveData(void* buffer, int len)
{
	int bytes = 0;

	if((bytes = recv(socketId, buffer, len, 0)) < 1)
	{
		throw std::runtime_error("Connection::receiveData Failed to receive bytes from server");
  	}

  	return bytes;
}

void Connection::close()
{
	::close(socketId);
}