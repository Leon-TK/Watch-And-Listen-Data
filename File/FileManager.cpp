#pragma once
#include "FileManager.h"
#include <fstream>
#include "IFile.h"
#include "../BufferManager.h"
#include "../FileChunkDispencer.h"

namespace WAL::File
{
    FileManager::FileManager(Interface::IFile* file, const size_t chunkSize) : file(file), chunkSize(chunkSize)
    {
        this->fileChunkDispenser = new FileChunkDispencer(this->file->GetBuffer(), this->chunkSize); //dctor
    }

    FileManager::~FileManager()
    {
        delete fileChunkDispenser;
    }

    std::vector<uint8_t> FileManager::GetNextChunk(size_t size, bool& outIsNextExist)
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

    bool FileManager::canGetNextChunk()
    {
        return false;
    }

}