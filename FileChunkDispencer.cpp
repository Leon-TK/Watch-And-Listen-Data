#pragma once
#include "FileChunkDispencer.h"
#include "BufferHandler.h"

namespace WAL
{
	FileChunkDispencer::FileChunkDispencer(std::ifstream& strm) : strm(strm)
	{
	}

	std::vector<uint8_t> FileChunkDispencer::GetNextChunk(size_t size, bool& outIsComplete)
	{
		FileBufferHandler fHandler(&this->strm);
		
		if (fHandler.canGetBeforeEnd(size))
		{
			return fHandler.GetDataBytes(size, false, outIsComplete);
		}
		else
		{
			return fHandler.GetDataBytes(size, false, outIsComplete);
		}
	}
}