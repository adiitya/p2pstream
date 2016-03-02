#include <server.h>
#include <stdexcept>
#include <string>
#include <iostream>

int main(int argc, char const *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr,"USAGE: ./server.exe <ownIP> <port>\n");
		exit(1);
	}

	try
	{
		Server server;
		std::cout<<"Server is running...."<<std::endl;
		server.startListening(atoi(argv[2]),argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cout<<"Catch these exception"<<std::endl;
		std::cerr<<e.what()<<std::endl;
		std::cerr<<strerror(errno)<<std::endl;
	}
	return 0;
}