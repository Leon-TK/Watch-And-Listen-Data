#pragma once
#include <fstream>
#include <vector>
#include "../ByteAssemble.h"
#include "../Vectors/Vec2.h"
#include "../Vectors/Vec3.h"

/*    
* Helper for extract pixels from binary buffer. You must to use buffer chunks instead as full one for better perfomance
*/    
namespace WAL
{
	/*template <typename T>
	class Vec3;
	template <typename T>
	class Vec2;*/

	/*
	* Extracts pixels from binary buffer
	* @param PixelType Which type of pixel to extract
	*/
	template <typename PixelType>
	class PixelExtractor final
	{
		typedef Vec3<PixelType> Pixel;
		typedef Vec2<uint16_t> Resolution;
		typedef std::vector<uint8_t> ByteVector;
		typedef std::vector<Pixel> PixelVector;
	private:
		size_t currentPosition{0};
		const size_t sizeToExtract{ 0 };
		/**
		* How much rows were not be getted by y step ignore. Used for next buffer y step correction
		*/
		size_t remainingRows{ 0 };

		/**
		* You can change buffer to new chunk by setbuffer()
		*/
		//std::ifstream* buffer;
		ByteVector* buffer;

		/**
		* Returns row of pixels with lenght as output resolution.X. Ignores some rows be Y step
		* @param step
		* @param maxLen
		*/
		PixelVector GetRow(size_t step, size_t maxLen);

		/**
		* How far do step for extrating pixels
		* @param dirRes
		* @param outRes
		*/
		size_t GetByteStep(Resolution& dirRes, Resolution& outRes);

		/**
		* returns true if rows with given length can fit to buffer without empty bytes at the end
		* @param rowLen
		* @param bufLen
		*/
		bool canRowsFitToBuffer(size_t rowLen, size_t bufLen);

		ByteVector GetPixelBytes();

		constexpr int GetComponentCount();

		size_t GetComponentBytesLen();

		PixelVector ConvertComponentBytesToPixels();

		bool canPixelTypesFitBuffer();

	public:
		PixelExtractor() = delete;
		//PixelExtractor(std::ifstream* buffer, const size_t sizeToExtract);
		PixelExtractor(ByteVector* buffer, const size_t sizeToExtract);

		/**
		* Returns nested rows in one 2D array. TODO must return filled rows, for that you need to do right calculation with chunk size in getNextChunk filehandler
		* @param step
		* @param maxLen
		*/
		PixelVector ExtractRow(size_t step, size_t maxLen);

		//void SetNewBuffer(std::ifstream* buffer);
		void SetNewBuffer(ByteVector* buffer);

		/*
		* Returns pixel while end of buffer is not reached
		*/
		Pixel GetNextPixel(bool& outIsNextPixelExist);

	};

	/*template <typename PixelType>
	inline PixelExtractor<PixelType>::PixelExtractor(std::ifstream* buffer, const size_t sizeToExtract) : buffer(buffer), sizeToExtract(sizeToExtract)
	{

	}*/

	template<typename PixelType>
	inline PixelExtractor<PixelType>::PixelExtractor(ByteVector* buffer, const size_t sizeToExtract): buffer(buffer)
	{
	}

	template <typename PixelType>
	inline std::vector<Vec3<PixelType>> PixelExtractor<PixelType>::ExtractRow(size_t step, size_t maxLen)
	{
	}

	template <typename PixelType>
	inline std::vector<Vec3<PixelType>> PixelExtractor<PixelType>::GetRow(size_t step, size_t maxLen)
	{
	}

	template <typename PixelType>
	inline size_t PixelExtractor<PixelType>::GetByteStep(Resolution& dirRes, Resolution& outRes)
	{
	}

	template <typename PixelType>
	inline bool PixelExtractor<PixelType>::canRowsFitToBuffer(size_t rowLen, size_t bufLen)
	{
		return (bufLen % rowLen) == 0;
	}

	template<typename PixelType>
	inline std::vector<uint8_t> PixelExtractor<PixelType>::GetPixelBytes()
	{
		//get n bytes from array. how much to take calculates by dirRes / outputRes 
		return ByteAssemble::DEPRECATED_GetBytesFrom<this->sizeToExtract>(this->buffer); //TODO chanke from template to common func
	}

	template<typename PixelType>
	inline constexpr int PixelExtractor<PixelType>::GetComponentCount()
	{
		return 3;
	}

	template<typename PixelType>
	inline size_t PixelExtractor<PixelType>::GetComponentBytesLen()
	{
		return (size_t)std::floor(this->sizeToExtract / this->GetComponentCount());
	}

	template<typename PixelType>
	inline std::vector<Vec3<PixelType>> PixelExtractor<PixelType>::ConvertComponentBytesToPixels()
	{
		if (canPixelTypesFitBuffer())
		{
			PixelVector pixels;
			const auto pixelCount = buffer->size() / sizeof(PixelType);

			//convert group of bytes to pixels
			for (int i = 0; i < pixelCount; i++)
			{
				std::array<uint8_t, sizeof(PixelType)> RawPixel;
				int g = 0;
				for (int j = 0; j < sizeof(PixelType); j++)
				{
					RawPixel[j] = buffer->at(g+j);
					g += sizeof(PixelType);
				}
				auto pixel = ByteAssemble::GlueBytes<sizeof(PixelType)>(RawPixel);
				pixels.push_back(pixel);
			}
			
			return pixels;
		}
		else
		{
			return PixelVector(0);
		}
		
	}

	template<typename PixelType>
	inline bool PixelExtractor<PixelType>::canPixelTypesFitBuffer()
	{
		return (buffer->size() % sizeof(PixelType)) == 0;
	}

	/*template <typename PixelType>
	inline void PixelExtractor<PixelType>::SetNewBuffer(std::ifstream* buffer)
	{
		this->buffer = buffer;
	}*/

	template<typename PixelType>
	inline void PixelExtractor<PixelType>::SetNewBuffer(ByteVector* buffer)
	{
		this->buffer = buffer;
	}

	template<typename PixelType>
	inline Vec3<PixelType> PixelExtractor<PixelType>::GetNextPixel(bool& outIsNextPixelExist)
	{
		if (!this->buffer)
		{
			outIsNextPixelExist = false;
			return Pixel();
		}

		if (this->sizeToExtract == 0)
		{
			outIsNextPixelExist = false;
			return Pixel(); //TODO through exception
		}

		auto pixelBytes = GetPixelBytes();

		auto componentLen = GetComponentBytesLen();

		PixelVector pixelBytes = ConvertComponentBytesToPixels();

		PixelVector RedPixels(componentLen);
		PixelVector GreenPixels(componentLen);
		PixelVector BluePixels(componentLen);

		int g = 0;
		for (int i = 0; i < componentLen; i++)
		{
			RedPixels.at(i) = pixelBytes.at(g);
			GreenPixels.at(i) = pixelBytes.at(g + 1);
			BluePixels.at(i) = pixelBytes.at(g + 2);
			g += GetComponentCount();
		}

		//PixelVector RedPixels(componentLen); //TODO have to be PixelVector
		//for (int i = 0; i < componentLen; i++)
		//{
		//	RedPixels.at(i) = pixelBytes.at(i);
		//}
		//PixelVector GreenPixels(componentLen);
		//for (int i = 0; i < componentLen; i++)
		//{
		//	GreenPixels.at(i) = pixelBytes.at(i + componentLen);
		//}
		//PixelVector BluePixels(componentLen);
		//for (int i = 0; i < componentLen; i++)
		//{
		//	BluePixels.at(i) = pixelBytes.at(i + (componentLen*2));
		//}
		// 
		
		//cast each chunk to array with type
		//get average in each chunk
		PixelType R = ByteAssemble::GetAverageFrom<PixelType>(RedPixels, componentLen);
		PixelType G = ByteAssemble::GetAverageFrom<PixelType>(GreenPixels, componentLen);
		PixelType B = ByteAssemble::GetAverageFrom<PixelType>(BluePixels, componentLen);
		//save average to 3 component of pixel
		//set new current position 
		return Pixel(R, G, B);
	}
}