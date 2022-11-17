#pragma once
#include "File_Impl.h"
#include <string>
#include "../BufferManager.h"

//#include <filesystem>
namespace WAL::File
{
    File_Impl::File_Impl(std::string& path)
    {
        this->Open(path);
    }

    void File_Impl::Open(std::string& path)
    {
        this->file.open(path, std::fstream::binary);
    }

    void File_Impl::Close()
    {
        this->file.close();
    }

    size_t File_Impl::GetFileSize()
    {
        BufferManagers::FileBufferManager manager(&this->file);
        return manager.GetFileSize();
    }

    std::ifstream& File_Impl::GetBuffer()
    {
        return file;
    }

}