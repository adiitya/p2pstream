#include <cstdio>
#include <iostream>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string.h>
#include <stdexcept>

using namespace std;

#define BUFFSIZE 1024
class Client
{
	public:
	bool sendmessage(char* serverIP, char* message, char* serverPort)
	{
		int sock; //socket descriptor
		struct sockaddr_in server; //socket structure
		char buffer[BUFFSIZE]; //message to be sent
		unsigned int messagelen; //length of message

		//create socket
		if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
			throw runtime_error("Socket creation failed in client\n");

		//clear the server socket structure
		memset(&server, 0, sizeof(server));

		//populate socket structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr(serverIP);
		server.sin_port = htons(atoi(serverPort));

		if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
			throw runtime_error("Failed to connect to server\n");


		messagelen = strlen(message);

		//send message
		if(send(sock, message, messagelen, 0) < 0)
			throw runtime_error("Failed to send message to server\n");

		fprintf(stdout, "Sent message to server: %s\n", message);

		//receive message from server
		int bytes ;
		if((bytes = recv(sock, buffer, BUFFSIZE, 0)) < 0)
			throw runtime_error("Failed to fetch message from server");

		buffer[bytes] = '\0';
		fprintf(stdout, "Received message from server: %s\n", buffer);

		if(bytes)
			return true;
		else
			return false;
	}

};
int main(int argc, char* argv[] )
{
	if(argc != 4)
	{
		fprintf(stderr,"USAGE: <filename> <ip_addr> <message>");
		exit(1);
	}
	//try catch block for all error handling
	try
	{
		Client obj;
		bool success = obj.sendmessage(argv[1], argv[2], argv[3]);
		if(success)
			cout<<"Communication Successful\n";
	}
	catch(const std::exception& e)
	{
		perror((string("Communication Failed - ") + e.what()).c_str());
	}
}

