#pragma once

/*    
* Convert raw image to specified format
*/    
namespace WAL
{
	namespace Images
	{
		namespace Interface
		{
			class IImage;
		}
	}
	namespace RawImages
	{
		template<typename, typename>
		class TRawImage;
	}

	namespace Converter
	{
		namespace Interface
		{
			template <typename PixelType>
			class IRawImageConverter
			{
			public:
				virtual ~IRawImageConverter() {};
				virtual WAL::Images::Interface::IImage* Convert(WAL::RawImages::TRawImage<PixelType, ResolutionType>& rawImg) = 0;

			};
		}
		
	}
	
}