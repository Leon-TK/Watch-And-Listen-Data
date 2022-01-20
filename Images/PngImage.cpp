#pragma once
#include "Png_Impl.h"
namespace WAL
{
    const std::vector<uint8_t>& PngImage::GetData() const
    {
        return ABaseImage::GetDataBase();
    }

}