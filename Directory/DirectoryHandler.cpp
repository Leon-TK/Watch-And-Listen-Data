#pragma once
#include "DirectoryHandler.h"
#include "../File/IFile.h"
#include "../File/File_Impl.h"
#include "../Vectors/Vec2.h"
#include "IDirectory.h"
#include <cmath>
namespace WAL
{
    DirectoryHandler::DirectoryHandler(IDirectory* dir) : dir(dir)
    {
    }

    DirectoryHandler::~DirectoryHandler()
    {
        delete dir;
    }

    size_t DirectoryHandler::GetAllFilesSize() const
    {
        if (!this->dir) return 0;

        size_t totalSize = 0;

        auto paths = this->dir->GetPaths();

        for (size_t i = 0; i < paths.size(); i++)
        {
            IFile* file = new File_Impl(paths.at(i));
            totalSize += file->GetFileSize();
        }

        return totalSize;
    }

    Vec2<uint16_t> DirectoryHandler::GetResolution(float aspectRatio) const
    {
        size_t dirSize = this->GetAllFilesSize();
        float x;
        float y;

        y = std::sqrt(dirSize / aspectRatio);
        x = aspectRatio * y;

        //TODO ceil or floor x and y for not missing data
        Vec2<uint16_t> res((uint16_t)x, (uint16_t)y);

        return res;
    }

}