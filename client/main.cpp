#include <client.h>
#define DEBUG
#include <iostream>
#include <cstring>

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
	std::string file;
	std::string IPaddr = argv[1];
	int port = atoi(argv[2]);
	std::cout<<"Enter file to be sent: "<<std::endl;
	std::cin>>file;
	Data data(file, 20, Data::TYPE::READ);
	try
	{
		Client client;
		//establishes the socket connection with server
		client.createConnection(IPaddr, port);
		//sends data 
		client.sendData(data);

		//client.receiveData();

		std::cout<<"message send "<<std::endl;

		//closes the socket connection
		client.closeConnection();
	}
	catch(std::exception& e)
	{
		std::cout<<"Exception form "<<e.what()<<std::endl;
	}
}