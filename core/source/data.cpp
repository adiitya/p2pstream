#include <data.h>

Data::Data(char* name, int length)
{
	fileName = name;
	chunkSize = length;

	fileStream.open(fileName, std::ifstream::in);
	if(!fileStream.is_open())
	{
		throw std::runtime_error("Data::Data Cannot open");
	}
}

Data::~Data()
{
	if(fileStream.is_open())
	{
		fileStream.close();
	}
}

int Data::getChunkSize()
{
	return chunkSize;
}


char* Data::getFileName()
{
	return fileName;
}

void Data::getData(char* buffer, int length)
{
	if(!fileStream.is_open())
	{
		throw std::runtime_error("Data::getData File is not opened to read");
		return;
	}
	if(length < chunkSize)
	{
		throw std::runtime_error("Data::getData Buffer size is small");
		return;
	}

	fileStream.read(buffer, chunkSize);
}