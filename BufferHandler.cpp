#include "BufferHandler.h"

std::vector<uint8_t> WAL::FileBufferHandler::ExtractData(size_t count)
{
	if (!strm) return std::vector<uint8_t>(0);

	std::vector<uint8_t> arr(count);
	for (size_t i = 0; i < count; i++)
	{
		arr.push_back(strm->get());
	}
	return arr;
}

WAL::FileBufferHandler::FileBufferHandler(std::ifstream* strm): strm(strm)
{

}

bool WAL::FileBufferHandler::canGetBeforeEnd(size_t count)
{
	if (!strm) return false;

	//check if all "get()" will fits in size, i.e. give data within size
	std::streampos beginPos = strm->tellg();
	strm->seekg(std::streamoff(count)); //try to reach next position
	if (strm->eof()) //check if position is end of file
	{
		strm->seekg(beginPos);
		return false;
	}
	else
	{
		strm->seekg(beginPos);
		return true;
	}
	//~
}

size_t WAL::FileBufferHandler::GetFileSize()
{
	if (!strm) return 0;

    auto beginPos = this->strm->tellg();
    this->strm->seekg(0, std::ifstream::end);
    auto endPos = strm->tellg();
    strm->seekg(beginPos);
    return endPos;
}

std::vector<uint8_t> WAL::FileBufferHandler::GetDataBytes(size_t count, bool doReturnPointer, bool& outIsComplete)
{
	if (!strm) return std::vector<uint8_t>(0);

	auto beginPos = strm->tellg();

	std::vector<uint8_t> arr(count);
	if (this->canGetBeforeEnd(count))
	{
		arr = this->ExtractData(count);
		if (doReturnPointer) strm->seekg(beginPos);
		outIsComplete = true;
		return arr;
	}
	else
	{
		auto beginPos = strm->tellg();
		strm->seekg(0, std::ifstream::end); //seek end
		auto eofPos = strm->tellg();
		strm->seekg(beginPos);

		auto offset = eofPos - beginPos;

		//extract remaining bytes
		arr = this->ExtractData(offset);

		if (doReturnPointer) strm->seekg(beginPos);
		outIsComplete = false;
		return arr;
	}
}
