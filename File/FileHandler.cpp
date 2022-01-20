#pragma once
#include "FileHandler.h"
#include <fstream>
#include "IFile.h"
#include "../BufferHandler.h"
#include "../FileChunkDispencer.h"

namespace WAL::File
{
    FileHandler::FileHandler(IFile* file) : file(file)
    {
    }

    std::vector<uint8_t> FileHandler::GetNextChunk(size_t size, bool& outIsNextExist)
    {
        if (file == nullptr) return std::vector<uint8_t>(0);
        
        FileChunkDispencer dispenser(this->file->GetBuffer());

        std::vector<uint8_t> data;

        bool isComplete = false;
        data = dispenser.GetNextChunk(size, isComplete);
        if (!isComplete) outIsNextExist = true; else outIsNextExist = false;
        return data;

    }

}