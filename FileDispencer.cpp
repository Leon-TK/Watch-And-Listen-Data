#pragma once
#include "FileDispencer.h"
#include "File/IFile.h"
#include "File/File_Impl.h"

namespace WAL::File
{
	FileDispencer::FileDispencer(const std::vector<std::string>& filePaths) : filePaths(filePaths)
	{
	}

	Interface::IFile* FileDispencer::GetNextFile(bool& outIsNextExist)
	{
		if (nextFileIndex == filePaths.size())
		{
			outIsNextExist = false;
			return nullptr; //all files was sended
		}
		outIsNextExist = true;

		auto filePath = filePaths.at(nextFileIndex);
		Interface::IFile* file = new File_Impl(filePath);
		nextFileIndex++;
		return file;
	}

}
