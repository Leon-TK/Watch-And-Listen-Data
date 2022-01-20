#pragma once
#include "Tif_Impl.h"

namespace WAL
{
	const std::vector<uint8_t>& TifImage::GetData() const
	{
		return ABaseImage::GetDataBase();
	}
}
