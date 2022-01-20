#pragma once
#include <string>

namespace WAL
{
	class IFile
	{
	public:
		virtual ~IFile() {};
		virtual void Open(std::string& path) = 0;
		virtual void Close() = 0;
		virtual size_t GetFileSize() = 0;
		virtual std::ifstream& GetBuffer() = 0;

	};
}