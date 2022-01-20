#pragma once
#include "IRawImageConverter.h"
#include "RawImage.h"

/*    
* Bridge for real converter
*/    
namespace WAL
{
	template<typename PixelType>
	class RawToPngConverter_Impl final : public IRawImageConverter<PixelType>
	{
	private:
		void* realPngConverter{ nullptr };

	public:

		RawToPngConverter_Impl() = default;
		virtual IImage* Convert(TRawImage<PixelType>& rawImg) override final;

	};

	template<typename PixelType>
	inline IImage* RawToPngConverter_Impl<PixelType>::Convert(TRawImage<PixelType>& rawImg)
	{
	}
}