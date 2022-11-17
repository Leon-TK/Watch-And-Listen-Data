#pragma once
#include "FileChunkDispencer.h"
#include "BufferManager.h"

namespace WAL::File
{
	FileChunkDispencer::FileChunkDispencer(std::ifstream& strm, const size_t chunkSize) : strm(strm), chunkSize(chunkSize)
	{
		fileBufferManager = new BufferManagers::FileBufferManager(&this->strm);
	}

	FileChunkDispencer::~FileChunkDispencer()
	{
		delete fileBufferManager;
	}

	std::vector<uint8_t> FileChunkDispencer::GetNextChunk(size_t size, bool& outIsNextExist, bool& outIsComplete)
	{
		if (this->canGetNextChunk())
		{
			auto data = this->fileBufferManager->GetDataBytes(size, false, outIsComplete);
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
		size_t remaining = 0;
		if (fileBufferManager->canGetBeforeEnd(this->chunkSize, remaining))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}