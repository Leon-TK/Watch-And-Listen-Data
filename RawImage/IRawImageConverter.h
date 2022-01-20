#pragma once
//#include "RawImage.h"
/*    
* Convert raw image to specified format
*/    
namespace WAL
{
	class IImage;
	template<typename pixelType>
	class RawImageArray;

	template <typename pixelType>
	class IRawImageConverter
	{
	public:
		virtual ~IRawImageConverter() {};
		virtual IImage* Convert(RawImageArray<pixelType>& rawImg) = 0;

	};
}