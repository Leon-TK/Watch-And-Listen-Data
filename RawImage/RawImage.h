#pragma once
#include <vector>

/*    
* Holds raw binary data in pixel containers. Should be converted to standart image formats except video encoder can work with raw data, otherwise you must convert raw data to foramt that encoder understand.
* template class
*/    
namespace WAL
{
	namespace RawImages
	{
		/**
		* Represents array of Pixel classes
		* @param PixelType which type of Pixel to use. See Pixels.h
		*
		*/
		template <typename PixelType, typename ResolutionType>
		class TRawImage
		{
			struct RawImageData
			{
				~RawImageData() { delete[] data; };
				RawImageData() = delete;
				RawImageData(const ResolutionType x, const ResolutionType y) : x(x), y(y)
				{
					data = new PixelType[(size_t)x * (size_t)y];
				}
				const ResolutionType x; //TODO must be unsigned
				const ResolutionType y; //TODO must be unsigned
				friend TRawImage<PixelType, ResolutionType>;
			private:
				PixelType* data = nullptr;
			};

			/*
			* At which index pixel will be puted by PutNextPixel()
			*/
			ResolutionType nextPxlX = 0;
			ResolutionType nextPxlY = 0;

			RawImageData* rawData = nullptr;
			

		public:
			typedef PixelType pixelType;
			typedef ResolutionType resolutionType;

			~TRawImage() { delete[] rawData; };
			TRawImage() = delete;
			TRawImage(const ResolutionType x, const ResolutionType y)
			{
				rawData = new RawImageData(x, y);
			}

			PixelType* GetData();
			size_t GetSize();
			size_t GetSizeX();
			size_t GetSizeY();

			/*
			* Put pixel at end of data
			* @param pxl Pixel to put
			*/
			void PutNextPixel(PixelType& pxl, bool& outIsNextPuttable);
			bool canPutNextPixel();
			void SetPixel(PixelType& pxl, ResolutionType x, ResolutionType y);
			PixelType GetPixel(ResolutionType x, ResolutionType y);
			void RestartPutNextPixel();
		};

		template <typename PixelType, typename ResolutionType>
		inline void TRawImage<PixelType, ResolutionType>::PutNextPixel(PixelType& pxl, bool& outIsNextPuttable)
		{
			if (canPutNextPixel())
			{
				if (nextPxlX == GetSizeX())
				{
					nextPxlY++;
					nextPxlX = 0;
					SetPixel(pxl, nextPxlX, nextPxlY);
					nextPxlX++;
					outIsNextPuttable = canPutNextPixel();
					return;
				}
				else
				{
					SetPixel(pxl, nextPxlX, nextPxlY);
					nextPxlX++;
					outIsNextPuttable = canPutNextPixel();
					return;
				}
			}
			else
			{
				outIsNextPuttable = false;
				return;
			}
		}

		template<typename PixelType, typename ResolutionType>
		inline bool TRawImage<PixelType, ResolutionType>::canPutNextPixel()
		{
			if ((nextPxlX == GetSizeX()) && (nextPxlY == GetSizeY() - 1)) return false;
			else return true;
		}

		template <typename PixelType, typename ResolutionType>
		inline PixelType* TRawImage<PixelType, ResolutionType>::GetData()
		{
			return rawData->data;
		}
		template<typename PixelType, typename ResolutionType>
		inline size_t TRawImage<PixelType, ResolutionType>::GetSize()
		{
			return ((size_t)rawData->x * (size_t)rawData->y);
		}
		template<typename PixelType, typename ResolutionType>
		inline size_t TRawImage<PixelType, ResolutionType>::GetSizeX()
		{
			return (size_t)rawData->x;
		}
		template<typename PixelType, typename ResolutionType>
		inline size_t TRawImage<PixelType, ResolutionType>::GetSizeY()
		{
			return (size_t)rawData->y;
		}
		template<typename PixelType, typename ResolutionType>
		inline void TRawImage<PixelType, ResolutionType>::SetPixel(PixelType& pxl, ResolutionType x, ResolutionType y)
		{
			rawData->data[(size_t)x + (size_t)y * GetSizeX()] = pxl;
		}
		template<typename PixelType, typename ResolutionType>
		inline PixelType TRawImage<PixelType, ResolutionType>::GetPixel(ResolutionType x, ResolutionType y)
		{
			return rawData->data[(size_t)x + (size_t)y * GetSizeX()];
		}
		template<typename PixelType, typename ResolutionType>
		inline void TRawImage<PixelType, ResolutionType>::RestartPutNextPixel()
		{
			nextPxlX = 0;
			nextPxlY = 0;
		}
	}
}