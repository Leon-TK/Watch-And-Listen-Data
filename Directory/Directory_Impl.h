#pragma once
#include "IDirectory.h"
#include <filesystem>
#include <string>

namespace WAL
{
	namespace Directory
	{
		namespace fs = std::filesystem;

		class Directory_Impl final : public Interface::IDirectory
		{
		private:
			const std::string root;
		public:
			Directory_Impl() = delete;
			Directory_Impl(const std::string& path);

			/**
			* returns paths of all files. Dirs are not included
			*/
			virtual const std::vector<std::string> GetPaths() const override final;
			virtual const std::string& GetRoot() const override final;

		};
	}
	
}