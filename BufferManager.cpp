#pragma once
#include "BufferManager.h"

namespace WAL::BufferManagers
{
	std::vector<uint8_t> FileBufferManager::ExtractData(size_t count)
	{
		if (!strm) return std::vector<uint8_t>(0);

		std::vector<uint8_t> arr(count);
		for (size_t i = 0; i < count; i++)
		{
			arr.push_back(strm->get());
		}
		return arr;
	}

	std::streampos FileBufferManager::TellEofPos()
	{
		auto beginPos = this->strm->tellg();
		this->strm->seekg(0, std::ifstream::end);
		auto endPos = strm->tellg();
		strm->seekg(beginPos);
		return endPos;
	}

	FileBufferManager::FileBufferManager(std::ifstream* strm) : strm(strm)
	{

	}

	bool FileBufferManager::canGetBeforeEnd(size_t count, size_t& outRemaining)
	{
		if (!strm) { outRemaining = 0; return false; }

		std::streampos beginPos = strm->tellg();
		strm->seekg(std::streamoff(count)); //try to reach next position
		std::streampos offsetPos = strm->tellg();
		if (strm->eof()) //check if position is end of file
		{
			auto eofPos = this->TellEofPos();
			auto diff = eofPos - beginPos;
			outRemaining = diff;
			strm->seekg(beginPos);
			return false;
		}
		else
		{
			strm->seekg(beginPos);
			outRemaining = 0;
			return true;
		}

	}

	size_t FileBufferManager::GetFileSize()
	{
		if (!strm) return 0;
		return this->TellEofPos();
	}

	std::vector<uint8_t> FileBufferManager::GetDataBytes(size_t count, bool doReturnPointer, bool& outIsComplete)
	{
		if (!strm) return std::vector<uint8_t>(0);

		auto beginPos = strm->tellg();

		std::vector<uint8_t> arr(count);
		size_t remaining = 0;
		if (this->canGetBeforeEnd(count, remaining))
		{
			arr = this->ExtractData(count);
			if (doReturnPointer) strm->seekg(beginPos);
			outIsComplete = true;
			return arr;
		}
		else
		{
			//extract remaining bytes
			arr = this->ExtractData(remaining);

			if (doReturnPointer) strm->seekg(beginPos);
			outIsComplete = false;
			return arr;
		}
	}
};

