#pragma once
#include "Directory_Impl.h"
#include <string>

namespace WAL::Directory
{

    Directory_Impl::Directory_Impl(const std::string& path): root(path)
    {
    };

    const std::vector<std::string> Directory_Impl::GetPaths() const
    {
        std::vector<std::string> paths;

        for (const auto& entry : fs::directory_iterator(this->root))
        {
            paths.push_back(entry.path().generic_string());
        }

        return paths;
    }

    const std::string& Directory_Impl::GetRoot() const
    {
        return this->root;
    }
}