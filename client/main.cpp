#include <client.h>

#include <iostream>
#include <cstring>
#include <string>

int main()
{
	char* data = "p2pstream project";
	std::string a = "cas";
	int port = 2045;

	try
	{
		Client client;
		client.createConnection(a, port);
		client.sendData((void*)data, strlen(data));
	}
	catch(std::exception& e)
	{
		std::cout<<"Exception form "<<e.what()<<std::endl;
	}
}