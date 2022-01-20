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

		std::streampos TellEofPos();
	public:
		FileBufferHandler() = delete;
		FileBufferHandler(std::ifstream* strm);
		/*
		* Checks can we get() data from buffer within count before the end
		* @param count Bytes count to check
		* @param outRemaining If result is false, this will tell how much bytes remain in stream
		*/
		bool canGetBeforeEnd(size_t count, size_t& outRemaining);
		size_t GetFileSize();
		/*
		* Get bytes from buffer
		* @param count How much bytes to get
		* @param doReturnPointer Whether to return stream pos to begin or not. I.e. seekg(begin)
		* @param outIsComplete True if we have got data with "count" lenght, False if less thatn "count". Also false means there is no next data bytes to extract
		*/
		std::vector<uint8_t> GetDataBytes(size_t count, bool doReturnPointer, bool &outIsComplete);

	};
}