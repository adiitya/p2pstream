#include <server.h>

void Server::startListening(int port)
{
	// make socket and accept client socket request to establish connection
	int clientsock;
	struct sockaddr_in server, client;

	if((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
		throw std::runtime_error("Server::startListening failed to create socket\n");
	memset(&server, 0, sizeof(server));       /* Clear struct */
    server.sin_family = AF_INET;                  /* Internet/IP */
    server.sin_addr.s_addr = htonl(INADDR_ANY);   /* Incoming addr */
    server.sin_port = htons(port);       /* server port */

	//bind function is used to relate the server fd and server structure
	if(bind(serversock, (struct sockaddr *) &server, sizeof(server)) < 0)
		throw std::runtime_error("Server::startListening failed to bind server fd to server structure\n");

	//To listen for incoming connecitons
	if(listen(serversock, MAXPENDING) < 0)
		throw std::runtime_error("Server::startListening couldn't listen to socket connection\n");

	while(1)
	{
		unsigned int clientlen;

		//to establish connection between client and server socket
		if((clientsock = accept(serversock, (struct sockaddr *) &client, &clientlen))< 0)
			throw std::runtime_error("Server::startListening failed to establish connection with client\n");

		fprintf(stdout, "Client connected: %s\n", inet_ntoa(client.sin_addr));
		
		respondToClient(clientsock);
	}	
}

void Server::respondToClient(int clientsock)
{
	Connection clientConn(clientsock);

	char buffer[1024] = {0};
	int bytes = clientConn.receiveData(buffer, 1024);

	printf("Received message from client: %s \n", buffer);

	clientConn.sendData("test data", 9);
	clientConn.close();
}
void Server::close()
{
	::close(serversock);
}