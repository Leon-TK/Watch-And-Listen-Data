#pragma once
#include "DirectoryManager.h"
#include "../File/IFile.h"
#include "../File/File_Impl.h"
#include "IDirectory.h"
#include <cmath>
#include "../Vectors/Vectors.h"
#include "../Math.h"

namespace WAL::Directory
{
    DirectoryManager::DirectoryManager(Interface::IDirectory* dir) : dir(dir)
    {
    }

    DirectoryManager::~DirectoryManager()
    {
        delete dir;
    }

    size_t DirectoryManager::GetAllFilesSize() const
    {
        if (!this->dir) return 0;

        size_t totalSize = 0;

        auto paths = this->dir->GetPaths();

        for (size_t i = 0; i < paths.size(); i++)
        {
            WAL::File::Interface::IFile* file = new WAL::File::File_Impl(paths.at(i));
            totalSize += file->GetFileSize();
        }

        return totalSize;
    }

    Vectors::TVec2<uint16_t> DirectoryManager::GetResolution(float aspectRatio) const
    {
        size_t dirSize = this->GetAllFilesSize();
        auto res = Math::CalcResolution<Vectors::TVec2<uint16_t>>(aspectRatio, dirSize);
        return res;
    }

}