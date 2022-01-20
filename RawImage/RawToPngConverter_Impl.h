#pragma once
#include "IRawImageConverter.h"
#include "RawImage.h"

/*    
* Bridge for real converter
*/    
namespace WAL
{
	template<typename RawImagePixelType>
	class RawToPngConverter_Impl final : public IRawImageConverter<RawImagePixelType>
	{
	private:
		void* realPngConverter{ nullptr };

	public:

		RawToPngConverter_Impl() = default;
		virtual IImage* Convert(RawImageArray<RawImagePixelType>& rawImg) override;

	};

	template<typename RawImagePixelType>
	inline IImage* RawToPngConverter_Impl<RawImagePixelType>::Convert(RawImageArray<RawImagePixelType>& rawImg)
	{
	}
}