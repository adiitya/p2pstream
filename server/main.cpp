#include <server.h>
#include <stdexcept>
#include <string>

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr,"USAGE: ./server.exe <port>\n");
		exit(1);
	}
	try
	{
		Server server;
		server.startListening(atoi(argv[1]));
	}
	catch(const std::exception& e)
	{
		perror((std::string("Communication Failed - ") + e.what()).c_str());
	}
	return 0;
}