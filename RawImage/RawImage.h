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
		template <typename PixelType>
		class TRawImage
		{
			struct Data
			{
				~Data() { delete[] data; };
				Data() = delete;
				Data(const uint32_t x, const uint32_t y) : x(x), y(y)
				{
					data = new PixelType[y][x];
				}

				PixelType* data{ nullptr };
				const uint32_t x;
				const uint32_t y;
			};

			/*
			* At which index pixel will be puted by PutNextPixel()
			*/
			uint32_t nextPxlX{0};
			uint32_t nextPxlY{0};

			Data* data{nullptr};
			

		public:
			~TRawImage() { delete[] data; };
			TRawImage() = delete;
			TRawImage(const uint32_t x, const uint32_t y)
			{
				data = new Data(x, y);
			}

			PixelType* GetData();
			size_t GetSize();
			uint32_t GetSizeX();
			uint32_t GetSizeY();

			/*
			* Put pixel at end of data
			* @param pxl Pixel to put
			*/
			void PutNextPixel(PixelType& pxl, bool& outIsNextPuttable);
			bool canPutNextPixel();
			void SetPixel(PixelType& pxl, uint32_t x, uint32_t y);
			PixelType GetPixel(uint32_t x, uint32_t y);
			void RestartNextPixel();
		};

		template <typename PixelType>
		inline void TRawImage<PixelType>::PutNextPixel(PixelType& pxl, bool& outIsNextPuttable)
		{
			if (canPutNextPixel())
			{
				if (nextPxlX == GetSizeX)
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

		template<typename PixelType>
		inline bool TRawImage<PixelType>::canPutNextPixel()
		{
			if ((nextPxlX == GetSizeX) && (nextPxlY == GetSizeY - 1)) return false;
			else return true;
		}

		template <typename PixelType>
		inline PixelType* TRawImage<PixelType>::GetData()
		{
			return data->data;
		}
		template<typename PixelType>
		inline size_t TRawImage<PixelType>::GetSize()
		{
			return data->x * data->y;
		}
		template<typename PixelType>
		inline uint32_t TRawImage<PixelType>::GetSizeX()
		{
			return data->x;
		}
		template<typename PixelType>
		inline uint32_t TRawImage<PixelType>::GetSizeY()
		{
			return data->y;
		}
		template<typename PixelType>
		inline void TRawImage<PixelType>::SetPixel(PixelType& pxl, uint32_t x, uint32_t y)
		{
			data->data[y][x] = pxl;
		}
		template<typename PixelType>
		inline PixelType TRawImage<PixelType>::GetPixel(uint32_t x, uint32_t y)
		{
			return data->data[y][x];
		}
		template<typename PixelType>
		inline void TRawImage<PixelType>::RestartNextPixel()
		{
			nextPxlX = 0;
			nextPxlY = 0;
		}
	}
}