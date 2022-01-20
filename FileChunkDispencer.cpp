#pragma once
#include "FileChunkDispencer.h"
#include "BufferHandler.h"

namespace WAL
{
	FileChunkDispencer::FileChunkDispencer(std::ifstream& strm, const size_t chunkSize) : strm(strm), chunkSize(chunkSize)
	{
		fileBufferHandler = new FileBufferHandler(&this->strm);
	}

	FileChunkDispencer::~FileChunkDispencer()
	{
		delete fileBufferHandler;
	}

	std::vector<uint8_t> FileChunkDispencer::GetNextChunk(size_t size, bool& outIsNextExist, bool& outIsComplete)
	{
		if (this->canGetNextChunk())
		{
			auto data = this->fileBufferHandler->GetDataBytes(size, false, outIsComplete);
			outIsNextExist = this->canGetNextChunk();
			return data;
		}
		else
		{
			outIsNextExist = false;
			outIsComplete = false;
			return std::vector<uint8_t>(0);
		}
	}

	bool FileChunkDispencer::canGetNextChunk()
	{
		if (fileBufferHandler->canGetBeforeEnd(this->chunkSize))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}