#pragma once
//#include "RawImage.h"
/*    
* Convert raw image to specified format
*/    
namespace WAL
{
	class IImage;
	template<typename PixelType>
	class TRawImage;

	template <typename PixelType>
	class IRawImageConverter
	{
	public:
		virtual ~IRawImageConverter() {};
		virtual IImage* Convert(TRawImage<PixelType>& rawImg) = 0;

	};
}