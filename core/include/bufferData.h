#ifndef BUFFER_DATA
#define BUFFER_DATA

#include <data.h>

class BufferData : public Data
{
	public:
		BufferData(void* data, long long size);			// to send data from memory

		int readData(void* buffer, int length);
		int writeData(void* buffer, int length);
		bool finish();
		int remainingData();
		void* getData();
		void reset();

	private:
		void* data;
		void* currentPointer;
		long long dataSize;
};

#endif /* BUFFER_DATA */