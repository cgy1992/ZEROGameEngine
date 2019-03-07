#ifndef INCLUDED_ZERO_SERIALIZATIONUTIL_H
#define INCLUDED_ZERO_SERIALIZATIONUTIL_H

#include <fstream>


namespace ZERO
{
	
	class SerializationUtil
	{

	public:
		SerializationUtil();
		~SerializationUtil();

		template<typename T>
		static void MessageSerialize(T message, std::fstream& fs, size_t dataSize = sizeof(T))
		{
			char* messageBuffer = new char[dataSize];
			memcpy(messageBuffer, &message, dataSize);
			fs.write(messageBuffer, dataSize);
		}

		template<typename T>
		static void MessageDeserialize(T& data, std::fstream& fs, size_t dataSize = sizeof(T))
		{
			fs.read((char*)&data, dataSize);
		}

	};
}//namespace ZERO

#endif // !INCLUDED_ZERO_SERIALIZATIONUTIL_H


