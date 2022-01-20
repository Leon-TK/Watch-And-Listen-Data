#pragma once
#include "IFile.h"
#include <fstream>
#include <string>

namespace WAL
{
	class File_Impl final : public IFile
	{
	private:
		std::ifstream file;
	public:
		File_Impl() = delete;
		File_Impl(std::string& path);

		virtual void Open(std::string& path) override final;
		virtual void Close() override final;
		virtual size_t GetFileSize() override final;
		virtual std::ifstream& GetBuffer() override final;

	};
}