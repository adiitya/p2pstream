#include <client.h>
#define DEBUG
#include <iostream>
#include <cstring>
#define BUFFLEN 1024

int main(int argc, char const *argv[])
{
	/**
	 * Server credentials(IPaddr and port) and the message to be sent(data)
	*/
	if(argc != 3)
	{
		std::cout<<"USAGE: ./client.exe <serverIPaddr> <port>\n";
		exit(1);
	}
	std::string data;
	std::string IPaddr = argv[1];
	int port = atoi(argv[2]);
	std::cout<<"Enter message to be sent: "<<std::endl;
	std::cin>>data;

	try
	{
		Client client;
		//establishes the socket connection with server
		client.createConnection(IPaddr, port);

		//sends data 
		client.sendData((void*)data.c_str(), data.size());

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