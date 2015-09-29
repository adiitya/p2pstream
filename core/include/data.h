#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <stdexcept>
#include <string>


/********************
*	Class: Data 	*
*********************/
// Data class represent the chunk of data 
// sent over connection.
// Chunk size is specified by the parameter 
// passed in constructor, everytime getData() is called
// that chunkSize is read

const int CHUNK_SIZE = 1024*1024;
const int MAX_FILE_NAME = 100;
const int MAX_HEADER_SIZE = MAX_FILE_NAME + 8;
struct MHeader
{
	/*
		This header is sent just after the connection is established.
		It contains name of the file and total length of the file in bytes.
		The header is of 108 bytes. (100--name, 8--length)
	*/
	char name[MAX_FILE_NAME];
	long long length;
};

class Data
{
public:
	enum TYPE
	{
		READ,
		WRITE
	};

	Data(std::string, int length, TYPE type);
	~Data();

	int getChunkSize();
	std::string getFileName();
	long long getFileSize();
	int readData(void* buffer, int length);
	int writeData(void* buffer, int length);
	bool finish();

private:
	std::string fileName;
	int chunkSize;

	std::fstream fileStream;
	long long fileSize;
};

#endif /* DATA_H */