#pragma once
#include <string>
#include <vector>
namespace WAL
{
	namespace Directory
	{
		namespace Interface
		{
			class IDirectory
			{
			public:
				virtual ~IDirectory() {};
				/**
				* returns paths of all files. Dirs are not included
				*/
				virtual const std::vector<std::string> GetPaths() const = 0;
				virtual const std::string& GetRoot() const = 0;

			};
		}
	}
}