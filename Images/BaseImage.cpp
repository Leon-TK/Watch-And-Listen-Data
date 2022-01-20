#pragma once
#include "ABaseImage.h"

namespace WAL
{
	const std::vector<uint8_t>& ABaseImage::GetDataBase() const
	{
		return data;
	}
}

