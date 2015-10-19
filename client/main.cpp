#include <client.h>
#include <iostream>
#include <cstring>
#include <data.h>

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
	std::getline(std::cin,file);

	Data* fileName = new BufferData(const_cast<char*>(file.c_str()), file.length());
	try
	{
		Client client;
		//establishes the socket connection with server
		client.createConnection(IPaddr, port);
		//sends data 
		client.sendData(*fileName, true);
		Data* data = new FileData(file, FileData::FTYPE::WRITE);
		client.receiveData(*data, true);

		std::cout<<"message send "<<std::endl;

		//closes the socket connection
		client.closeConnection();
	}
	catch(std::exception& e)
	{
		std::cout<<"Catch these exception"<<std::endl;
		std::cerr<<e.what()<<std::endl;
		std::cerr<<strerror(errno)<<std::endl;
	}
	delete fileName;
}