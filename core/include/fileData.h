#ifndef FILE_DATA
#define FILE_DATA

#include <data.h>

#include <fstream>
#include <string>

class FileData : public Data 
{
public:
	enum TYPE
	{
		WRITE,
		READ
	};
	FileData(std::string fileName, TYPE type);
	~FileData();

	int readData(void* buffer, int length);
	int writeData(void* buffer, int length);
	bool finish();

	std::string getFileName();
	long long getFileSize();

private:
	std::string fileName;
	std::fstream fileStream;
	long long fileSize;
};

#endif /* FILE_DATA */