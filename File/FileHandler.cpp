#pragma once
#include "FileHandler.h"
#include <fstream>
#include "IFile.h"
#include "../BufferHandler.h"
#include "../FileChunkDispencer.h"

namespace WAL::File
{
    FileHandler::FileHandler(Interface::IFile* file, const size_t chunkSize) : file(file), chunkSize(chunkSize)
    {
        this->fileChunkDispenser = new FileChunkDispencer(this->file->GetBuffer(), this->chunkSize); //dctor
    }

    FileHandler::~FileHandler()
    {
        delete fileChunkDispenser;
    }

    std::vector<uint8_t> FileHandler::GetNextChunk(size_t size, bool& outIsNextExist)
    {
        if (file == nullptr)
        {
            outIsNextExist = false;
            return std::vector<uint8_t>(0);
        }
        
        if (canGetNextChunk())
        {

        }
        

        std::vector<uint8_t> data;

        bool isComplete = true;
        bool isNextExist = true;
        data = fileChunkDispenser->GetNextChunk(size, isNextExist, isComplete);
        if (!isComplete) outIsNextExist = true; else outIsNextExist = false;

        return data;

    }

    bool FileHandler::canGetNextChunk()
    {
        return false;
    }

}