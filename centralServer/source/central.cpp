#include <central.h>

//std::multimap<std::string, std::string> CentralServer::fileToIP = std::multimap<std::string, std::string>(); 
CentralServer::CentralServer() 
{
	createMap();
}

CentralServer::~CentralServer()
{	
}

void CentralServer::startListening(int port, std::string serverIP)
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

	//std::cout<<connThreads.size()<<std::endl;
	pthread_t thread;
	while(true)
	{
		unsigned int clientlen = sizeof(struct sockaddr_in);

		if((clientSock = accept(serversock, (struct sockaddr *) &client, &clientlen)) == -1)
			throw std::runtime_error("Server::startListening: Failed to establish connection with client");

		std::cout<<inet_ntoa(client.sin_addr)<<" connected"<<std::endl;
	
		//connThreads.push_back(tmp);
		
		if(pthread_create(&thread, NULL, respondToClient, (void*)&clientSock) < 0)
			throw std::runtime_error("Server::startListening: Cannot create thread");
		
	//	respondToClient((void*)&clientSock);
		//std::cout<<connThreads.size()<<" host connected"<<std::endl;	
	}	
}

void* CentralServer::respondToClient(void* clientSock)
{
	CentralServer cs;
	Connection clientConn(*((int*)clientSock));
	char name[100] = {0};
	Data* dataRec = new BufferData(name, 100);
	clientConn.receiveData(*dataRec, false);
	std::string IP = cs.getIP(name);
	memcpy(name, IP.c_str(), IP.length());
	std::cout<<name<<std::endl;
	Data* dataSend = new BufferData(name, 100);
	clientConn.sendData(*dataSend, true);
	printf("Message sent to client: %d \n", *((int*)clientSock));
	clientConn.close();
	delete dataRec;
	delete dataSend;
	return NULL;
}

void CentralServer::createMap()
{
	std::ifstream myfile("fileToIP.txt");
	std::string file,ip;
	//std::cout<<"Creating MAP : File -> UserIP"<<std::endl;
	if(myfile.is_open())
	{	
		while(!myfile.eof())
		{
			myfile>>file;
			myfile>>ip;
			fileToIP.insert(std::pair<std::string, std::string>(file,ip));
		}
		//for(mmi itr = fileToIP.begin();itr!=fileToIP.end();itr++)
			//std::cout<<itr->first <<"  "<<itr->second<<std::endl;
	}
}

std::string CentralServer::getIP(std::string filename)
{
	std::string IP = "";
	std::pair<mmi, mmi> ret;
	ret = fileToIP.equal_range(filename);

	for(mmi itr = ret.first; itr != ret.second; itr++){
		IP += itr->second+" ";
	}
	return IP;
}