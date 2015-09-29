#include <server.h>
#include <iostream>

Server::~Server()
{
	close();
}

void Server::startListening(int port, std::string serverIP)
{
	int clientSock;
	struct sockaddr_in server, client;

	if((serversock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		throw std::runtime_error("Server::startListening: Failed to create server listening socket");

	memset(&server, 0, sizeof(struct sockaddr_in));

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(server.sin_family, serverIP.c_str(), &server.sin_addr.s_addr);
    
	if(bind(serversock, (struct sockaddr*) &server, sizeof(struct sockaddr_in)) == -1)
		throw std::runtime_error("Server::startListening: Failed to bind server fd to server structure");

	
	if(listen(serversock, MAXPENDING) == -1)
		throw std::runtime_error("Server::startListening: Couldn't listen to socket connection");

	while(true)
	{
		unsigned int clientlen = sizeof(struct sockaddr_in);

		if((clientSock = accept(serversock, (struct sockaddr *) &client, &clientlen)) == -1)
			throw std::runtime_error("Server::startListening: Failed to establish connection with client");

		std::cout<<inet_ntoa(client.sin_addr)<<" connected"<<std::endl;
		

		respondToClient(clientSock);
		
	}	
}

void Server::respondToClient(int clientSock)
{
	Connection clientConn(clientSock);
	clientConn.receiveData();

	printf("Received message from client: \n");

	clientConn.close();
}

void Server::close()
{
	if(::close(serversock) == -1)
		throw std::runtime_error("Server::close: Cannot close server listening socket");
}