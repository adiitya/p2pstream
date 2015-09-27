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
	int readData(void* buffer, int length);
	int writeData(void* buffer, int length);
	bool finish();

private:
	std::string fileName;
	int chunkSize;

	std::fstream fileStream;
};

#endif /* DATA_H */