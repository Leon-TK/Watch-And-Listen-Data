#pragma once
#include <vector>
#include <string>

namespace WAL
{
	class IFile;

	/*
	* Class that responsible for giving files.
	*/
	class FileDispencer final
	{
	private:
		size_t nextFileIndex{0};
		/*
		* Paths from which dispence
		*/
		const std::vector<std::string> filePaths;
	public:
		FileDispencer() = delete;
		FileDispencer(const std::vector<std::string>& filePaths);

		/*
		* Returns file from filePaths array
		* Returns nullptr if no more files remain. TODO should I create alt approach for nullptr case?
		*/
		IFile* GetNextFile(bool& outIsNextExist);

	};
}