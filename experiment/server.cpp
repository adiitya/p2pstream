#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdexcept>

#define MAXPENDING 5    /* Max connection requests */
#define BUFFSIZE 32
//void Die(char *mess) { perror(mess); exit(1); }//this functio was not used anywhere..
using namespace std;
class Server
{
	public:
	bool respondToClient(int clientsock)
	{
		//Size of received message
		int received = -1;

		//Message to be received
		char buffer[BUFFSIZE];

		//Receive message from client
		if((received = recv(clientsock, buffer, BUFFSIZE, 0)) < 0)
			throw runtime_error("Failed to receive message from client\n");

		cout<<"Received message from client: "<<buffer<<endl;

		//Message to be sent
		char message[BUFFSIZE];
		printf("Enter the message to be sent to client\n");
		cin>>message;

		if(send(clientsock, message, BUFFSIZE, 0) < 0)
			return false;
		else
			return true;
	}
};
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr,"USAGE: ./server <port>\n");
		exit(1);
	}

	try
	{
		// make socket and accept client socket request to establish connection
		int serversock, clientsock;
		struct sockaddr_in server, client;

		if((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
			throw runtime_error("Socket creation failed in server\n");
		memset(&server, 0, sizeof(server));       /* Clear struct */
	    server.sin_family = AF_INET;                  /* Internet/IP */
	    server.sin_addr.s_addr = htonl(INADDR_ANY);   /* Incoming addr */
	    server.sin_port = htons(atoi(argv[1]));       /* server port */

		//bind function is used to relate the server fd and server structure
		if(bind(serversock, (struct sockaddr *) &server, sizeof(server)) < 0)
			throw runtime_error("Failed to bind server fd to server structure\n");

		//To listen for incoming connecitons
		if(listen(serversock, MAXPENDING) < 0)
			throw runtime_error("Couldn't listen to socket connection\n");

		while(1)
		{
			unsigned int clientlen = sizeof(client);

			//to establish connection between client and server socket
			if((clientsock = accept(serversock, (struct sockaddr *) &client, &clientlen))< 0)
				throw runtime_error("Failed to establish connection with client\n");

			fprintf(stdout, "Client connected: %s\n", inet_ntoa(client.sin_addr));
			Server obj;
			
			if(obj.respondToClient(clientsock) == false) 
				throw runtime_error("Failed to send message to client\n");

			close(clientsock);
		}
	}
	catch(const std::exception& e)
	{
		perror((string("Communication Failed - ") + e.what()).c_str());
	}
}