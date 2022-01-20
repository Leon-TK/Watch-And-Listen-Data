#pragma once
#include "IDirectory.h"
#include <filesystem>
#include <string>

namespace WAL
{
	namespace fs = std::filesystem;

	class Directory_Impl final : public IDirectory
	{
	private:
		std::string root;
	public:
		Directory_Impl() = delete;
		Directory_Impl(std::string& path);

		virtual const std::vector<std::string> Open(std::string& path) override;

		/**
		* returns paths of all files. Dirs are not included
		*/
		virtual const std::vector<std::string> GetPaths() const override final;
		virtual const std::string& GetRoot() const override final;

	};
}