#include <fileData.h>

#include <iostream>

FileData::FileData(std::string name, FTYPE type)
{
	fileName = name;
	//std::cout<<fileName<<std::endl;
	
	if(type == FTYPE::READ)
		fileStream.open(fileName, std::ifstream::in);
	else
		fileStream.open(fileName, std::ofstream::out);

	if(!fileStream.is_open())
	{
		throw std::runtime_error("FileData::FileData: File cannot be opened");
	}

	fileStream.seekg(0, fileStream.end);
	if(type == FTYPE::READ)
		fileSize = fileStream.tellg();
	fileStream.seekg(0, fileStream.beg);
}

FileData::~FileData()
{
	if(fileStream.is_open())
	{
		fileStream.close();
	}
}

std::string FileData::getFileName()
{
	return fileName;
}

long long FileData::getFileSize()
{
	return fileSize;
}

bool FileData::finish()
{
	return fileStream.eof();
}


int FileData::readData(void* buffer, int length)
{
	if(!fileStream.is_open())
	{
		throw std::runtime_error("FileData::getData: File is not opened to read");
	}
	if(length < CHUNK_SIZE)
	{
		throw std::runtime_error("FileData::getData: Buffer size is small");
	}

	std::cout<<fileSize<<" : "<<fileStream.tellg()<<std::endl;
	long long readLen = fileSize - fileStream.tellg();
	if(readLen > CHUNK_SIZE)
		readLen = CHUNK_SIZE;
	
	std::cout<<readLen<<std::endl;
	if(readLen < CHUNK_SIZE)
		fileStream.read((char *)buffer, readLen + 1); //Here +1 denotes eof
	else
		fileStream.read((char *)buffer, readLen);
	return readLen;
}

int FileData::writeData(void* buffer, int length)
{
	if(!fileStream.is_open())
	{
		throw std::runtime_error("FileData:writeData: File is not opened to write");
	}
	if(length > CHUNK_SIZE)
	{
		throw std::runtime_error("FileData::writeData: Buffer size is big");
	}

	fileStream.write((char*) buffer, length);

	return length;
}