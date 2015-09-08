#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <stdexcpt>


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
	Data(char* name, int length);
	~Data();

	int getChunkSize();
	char* getFileName();
	void getData(char* buffer, int length);

private:
	char* fileName;
	int chunkSize;

	ifstream fileStream;
};

#endif /* DATA_H */