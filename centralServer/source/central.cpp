#include <central.h>

//std::multimap<std::string, std::string> CentralServer::fileToIP = std::multimap<std::string, std::string>(); 
CentralServer::CentralServer() 
{
	createMap();
}

CentralServer::~CentralServer()
{	
}

void* CentralServer::respondToClient(void* clientSock)
{
	Connection clientConn(*((int*)clientSock));
	char name[100] = {0};
	Data* dataRec = new BufferData(name, 100);
	clientConn.receiveData(*dataRec);
	std::string IP = getIP(name);
	memcpy(name, IP.c_str(), IP.length());
	std::cout<<name<<std::endl;
	Data* dataSend = new BufferData(name, 100);
	clientConn.sendData(*dataSend);
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
	if(myfile.is_open())
	{	
		while(!myfile.eof())
		{
			myfile>>file;
			myfile>>ip;
			fileToIP.insert(std::pair<std::string, std::string>(file,ip));
		}
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