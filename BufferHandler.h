#pragma once
#include <fstream>
#include <vector>

namespace WAL
{
	class FileBufferHandler final
	{
	private:
		std::ifstream* strm;

		std::vector<uint8_t> ExtractData(size_t count);
	public:
		FileBufferHandler() = delete;
		FileBufferHandler(std::ifstream* strm);
		/*
		* Checks can we get() data from buffer within count before the end
		*/
		bool canGetBeforeEnd(size_t cout);
		size_t GetFileSize();
		/*
		* Get bytes from buffer
		* @param count How much bytes to get
		* @param doReturnPointer Whether to return stream pointer to begin or not. I.e. seekg(begin)
		* @param True if we have got data with "count" lenght, False if less thatn "count"
		*/
		std::vector<uint8_t> GetDataBytes(size_t count, bool doReturnPointer, bool &outIsComplete);

	};
}