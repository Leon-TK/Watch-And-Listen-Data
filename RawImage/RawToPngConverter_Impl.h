#pragma once
#include "IRawImageConverter.h"
#include "RawImage.h"

/*    
* Bridge for real converter
*/    
namespace WAL
{
	namespace Converter
	{
		template<typename PixelType>
		class RawToPngConverter_Impl final : public Interface::IRawImageConverter<PixelType>
		{
		private:
			void* realPngConverter{ nullptr };

		public:

			RawToPngConverter_Impl() = default;
			virtual WAL::Images::Interface::IImage* Convert(WAL::RawImages::TRawImage<PixelType, ResolutionType>& rawImg) override final;

		};

		template<typename PixelType>
		inline WAL::Images::Interface::IImage* RawToPngConverter_Impl<PixelType>::Convert(WAL::RawImages::TRawImage<PixelType, ResolutionType>& rawImg)
		{
			return nullptr;
		}
	}
	
}