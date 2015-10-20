#include <bufferData.h>

#include <string>
#include <cstring>

BufferData::BufferData(void* data, long long size)
{
    this->data = currentPointer = data;
	dataSize = size;
}

void* BufferData::getData()
{
	return data;
}

void BufferData::reset()
{
	currentPointer = data;
}

int BufferData::readData(void* buffer, int size)
{
	// read from BufferData.data, write to buffer
	// used for send from socket

	int dataToCopy = CHUNK_SIZE;
	if(remainingData() < CHUNK_SIZE)
		dataToCopy = remainingData();

	if(size < dataToCopy)
		throw std::runtime_error("BufferData::readData: Buffer less size");

	memcpy(buffer, currentPointer, dataToCopy);
	currentPointer = (char*)currentPointer + dataToCopy;
	
	return dataToCopy;
}

int BufferData::writeData(void* buffer, int size)
{
	// read from buffer, write to BufferData.data
	// used for receiving from socket

	if((char*)currentPointer + size > (char*)data + dataSize)
		throw std::runtime_error("BufferData::writeData: Data buffer less");

	memcpy(currentPointer, buffer, size);
	currentPointer = (char*)currentPointer + size;

	return size;
}

bool BufferData::finish()
{	
	return ((char*)currentPointer - (char*)data) >= dataSize;
}

int BufferData::remainingData()
{
	return (char*)data - (char*)currentPointer + dataSize;
}