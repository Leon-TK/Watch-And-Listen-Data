#pragma once
#include "Images.h"

namespace WAL::Images
{
    const std::vector<uint8_t>& JpgImage::GetData() const
    {
        return ABaseImage::GetDataBase();
    }
    const std::vector<uint8_t>& PngImage::GetData() const
    {
        return ABaseImage::GetDataBase();
    }
    const std::vector<uint8_t>& TifImage::GetData() const
    {
        return ABaseImage::GetDataBase();
    }
    const std::vector<uint8_t>& ABaseImage::GetDataBase() const
    {
        return data;
    }
}
