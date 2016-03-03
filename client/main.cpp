#include <client.h>
#include <iostream>
#include <cstring>
#include <data.h>
#include <unistd.h>

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
	std::cout<<"What would you like to watch today? "<<std::endl;
	std::getline(std::cin,file);
	int id = fork();
	if(id == 0)
	{
		execl("../videoPlayer/player.exe", file.c_str());
	}
	else
	{
		Data* fileName = new BufferData(const_cast<char*>(file.c_str()), file.length());
		try
		{
			Client client;
			//establishes the socket connection with server
			client.createConnection(IPaddr, port);
			//sends data 
			client.sendData(*fileName, true);
			char ips[100] = {0};
			Data* data = new BufferData(ips, 100);
			client.receiveData(*data, true);
			std::cout<<"File "<<file<<" found at IP "<<ips<<std::endl;
			std::cout<<"Requesting File Stream from peer "<<ips<<" ..."<<std::endl;

			//closes the socket connection
			client.closeConnection();
			
			char* first_ip = strtok(ips, " ");
			client.createConnection(first_ip, 2050);
			((BufferData*)fileName)->reset();
			//std::cout<<((char*)((BufferData*)(fileName))->getData())<<std::endl;
			client.sendData(*fileName, true);

			Data* actual_file = new FileData(file, FileData::FTYPE::WRITE);
			client.receiveData(*actual_file, true);

			std::cout<<"Multimedia Streaming : Success"<<std::endl;
			
			delete data;
			delete actual_file;
		}
		catch(std::exception& e)
		{
			std::cout<<"Catch these exception"<<std::endl;
			std::cerr<<e.what()<<std::endl;
			std::cerr<<strerror(errno)<<std::endl;
		}
		delete fileName;
	}
}