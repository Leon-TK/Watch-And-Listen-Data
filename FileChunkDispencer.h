#pragma once
#include <fstream>
#include <vector>

namespace WAL
{
	namespace BufferManagers
	{
		class FileBufferManager;
	}

	namespace File
	{
		/*
	* Class that responsible for giving chunks of file.
	*/
		
		class FileChunkDispencer final
		{
		private:
			/*
			* File stream that will be processed
			*/
			std::ifstream& strm;

			const size_t chunkSize{ 0 };
			size_t processeddBytes{ 0 };
			BufferManagers::FileBufferManager* fileBufferManager;
		public:
			FileChunkDispencer() = delete;
			FileChunkDispencer(std::ifstream& strm, const size_t chunkSize);
			~FileChunkDispencer();

			/*
			* Returns bytes chunk of current file.
			* @param size How big chunk to extract
			* @param outIsComplete returns true if it can extract chunk, false means that in file stream less bytes than you want extract
			*/
			std::vector<uint8_t> GetNextChunk(size_t size, bool& outIsNextExist, bool& outIsComplete); //TODO what type to return?
			bool canGetNextChunk();
		};
	}
}