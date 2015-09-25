#include <client.h>
#define DEBUG
#include <iostream>
#include <cstring>
#define BUFFLEN 1024

int main()
{
	/**
	 * Server credentials(IPaddr and port) and the message to be sent(data)
	*/
	char* data = "p2pstreamproject";
	std::string IPaddr = "10.42.0.1";
	int port = 2045;

	try
	{
		Client client;
		//establishes the socket connection with server
		client.createConnection(IPaddr, port);

		//sends data 
		client.sendData((void*)data, strlen(data));

		char buffer[BUFFLEN] = {0};
		client.receiveData(buffer, BUFFLEN);

		std::cout<<"Received message: "<<buffer<<std::endl;

		//closes the socket connection
		client.closeConnection();
	}
	catch(std::exception& e)
	{
		std::cout<<"Exception form "<<e.what()<<std::endl;
	}
}