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

bool Data::finish()
{
	return fileStream.eof();
}


void Data::readData(void* buffer, int length)
{
	if(!fileStream.is_open())
	{
		throw std::runtime_error("Data::getData: File is not opened to read");
	}
	if(length < chunkSize)
	{
		throw std::runtime_error("Data::getData: Buffer size is small");
	}

	fileStream.read((char *)buffer, chunkSize);
}

void Data::writeData(void* buffer, int length)
{
	if(!fileStream.is_open())
	{
		throw std::runtime_error("Data:writeData: File is not opened to write");
	}
	if(length < chunkSize)
	{
		throw std::runtime_error("Data::writeData: Buffer size is small");
	}

	fileStream.write((char*) buffer, chunkSize);
}