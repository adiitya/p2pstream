#ifndef DATA_H
#define DATA_H

#include <stdexcept>

/********************
*	Class: Data 	*
*********************/
// Data class represent the chunk of data 
// sent over connection.
// Chunk size is specified by the parameter 
// passed in constructor, everytime getData() is called
// that chunkSize is read

const int CHUNK_SIZE = 1024 * 1024;

class Data
{
public:
	//StringData(std::string fileName);				// to send file
	//~Data();

	//std::string getFileName();
	//long long getFileSize();
	virtual int readData(void* buffer, int length);
	virtual int writeData(void* buffer, int length);
	virtual bool finish();
};

#endif /* DATA_H */