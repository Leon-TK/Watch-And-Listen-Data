#pragma once
#include <fstream>
#include <vector>

namespace WAL
{
	/*
	* Class that responsible for giving chunks of file.
	*/
	class FileBufferHandler;

	class FileChunkDispencer final
	{
	private:
		/*
		* File stream that will be handled
		*/
		std::ifstream& strm;

		const size_t chunkSize{ 0 };
		size_t handledBytes{ 0 };
		FileBufferHandler* fileBufferHandler;
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

	class StreamChunkManager
	{
	private:
		std::ifstream& strm;
	public:
		//void Init(std::ifstream* strm);
	};
}