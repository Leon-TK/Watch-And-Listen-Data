#pragma once
#include "h256_Impl.h"
#include <string>

namespace WAL
{
    void h256Encoder::SaveAsFile(std::string& path)
    {

    }

    void h256Encoder::AddAsFrame(IImage* img)
    {
        this->images.push_back(img);
    }

    void h256Encoder::EncodeFrames()
    {

    }

    void h256Encoder::AddAsFrames(std::vector<IImage*>& imgs)
    {
        for (size_t i = 0; i < imgs.size(); i++)
        {
            this->images.push_back(imgs.at(i));
        }
    }
}
