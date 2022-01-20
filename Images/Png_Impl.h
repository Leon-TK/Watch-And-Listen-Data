#pragma once
#include "ABaseImage.h"
#include "IImage.h"

namespace WAL
{
	class PngImage final : public ABaseImage, public IImage
	{
	public:
		virtual const std::vector<uint8_t>& GetData() const override final;

	};
}