#pragma once
#include "Jpg_Impl.h"
namespace WAL
{
    const std::vector<uint8_t>& JpgImage::GetData() const
    {
        return ABaseImage::GetDataBase();
    }
}
