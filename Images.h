#pragma once
#include "Images/IImage.h"
#include <vector>

namespace WAL
{
	namespace Images
	{
	
		using namespace WAL::Images::Interface;

		class ABaseImage
		{
		private:
			std::vector<uint8_t> data;
		public:
			const std::vector<uint8_t>& GetDataBase() const;

		};

		class TifImage final : public ABaseImage, public IImage
		{
		public:
			virtual const std::vector<uint8_t>& GetData() const override final;

		};
		class PngImage final : public ABaseImage, public IImage
		{
		public:
			virtual const std::vector<uint8_t>& GetData() const override final;

		};
		class JpgImage final : public ABaseImage, public IImage
		{
		public:
			virtual const std::vector<uint8_t>& GetData() const override final;

		};
	}
}