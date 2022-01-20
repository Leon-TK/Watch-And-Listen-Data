#pragma once
#include <string>
#include <vector>
namespace WAL
{
	class IDirectory
	{
	public:
		virtual ~IDirectory() {};
		virtual const std::vector<std::string> Open(std::string& path) = 0;
		/**
		* returns paths of all files. Dirs are not included
		*/
		virtual const std::vector<std::string> GetPaths() const = 0;
		virtual const std::string& GetRoot() const = 0;

	};
}