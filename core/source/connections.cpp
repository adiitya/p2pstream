#include "../include/connections.h"

Connection::Connection(int sock)
{
	type = CONN_TYPE::SERVER_CONN;
	sock_fd = sock;
}
Connection::Connection(char* ip, int port)
{
	type = CONN_TYPE::CLIENT_CONN;
	this->ip = ip;
	this->port = port;
	memset(&socketAddr, 0, sizeof(socketAddr));
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_addr.s_addr = inet_addr(ip);
	socketAddr.sin_port = htons(port);
	//Creating socket
	if ((sock_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
	{
		throw std::runtime_error("Connection::Failed to create socket");
	}
	//Connecting to created socket
	if(connect(sock_fd, (struct sockaddr *) &socketAddr, sizeof(socketAddr)) < 0) 
	{
		throw std::runtime_error("Connection::Unable to connect");
	}
}
char* Connection::getIp()
{
	return (type == CLIENT_CONN)?ip:NULL;
}
int Connection::getPort()
{
	return (type == CLIENT_CONN)?port:-1;
}
void Connection::sendData(char* message)
{
	size_t echolen = strlen(message);
	if (send(sock_fd, message, echolen, 0) != echolen) {
		throw std::runtime_error("Connection::Mismatch in number of sent bytes");
	}
}
int Connection::recData(char *buffer, int BUFFSIZE)
{
	int bytes = 0;
	if ((bytes = recv(sock_fd, buffer, BUFFSIZE-1, 0)) < 1) {
		throw std::runtime_error("Connection::Failed to receive bytes from server");
  	}
}
