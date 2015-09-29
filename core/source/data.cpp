#include <data.h>

#include <iostream>

Data::Data(std::string name, int length, TYPE type)
{
	fileName = name;
	chunkSize = length;

	if(type == TYPE::READ)
		fileStream.open(fileName, std::ifstream::in);
	else
		fileStream.open(fileName, std::ofstream::out);

	if(!fileStream.is_open())
	{
		throw std::runtime_error("Data::Data: File cannot be opened");
	}

	fileStream.seekg(0, fileStream.end);
	if(type == TYPE::READ)
		fileSize = fileStream.tellg();
	fileStream.seekg(0, fileStream.beg);
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


std::string Data::getFileName()
{
	return fileName;
}

long long Data::getFileSize()
{
	return fileSize;
}

bool Data::finish()
{
	return fileStream.eof();
}


int Data::readData(void* buffer, int length)
{
	if(!fileStream.is_open())
	{
		throw std::runtime_error("Data::getData: File is not opened to read");
	}
	if(length < chunkSize)
	{
		throw std::runtime_error("Data::getData: Buffer size is small");
	}

	std::cout<<fileSize<<" : "<<fileStream.tellg()<<std::endl;
	long long readLen = fileSize - fileStream.tellg();
	if(readLen > chunkSize)
		readLen = chunkSize;
	
	std::cout<<readLen<<std::endl;
	if(readLen < chunkSize)
		fileStream.read((char *)buffer, readLen + 1);
	else
		fileStream.read((char *)buffer, readLen);
	return readLen;
}

int Data::writeData(void* buffer, int length)
{
	if(!fileStream.is_open())
	{
		throw std::runtime_error("Data:writeData: File is not opened to write");
	}
	if(length > chunkSize)
	{
		throw std::runtime_error("Data::writeData: Buffer size is big");
	}

	fileStream.write((char*) buffer, length);

	return length;
}