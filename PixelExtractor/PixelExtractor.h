#pragma once
#include <fstream>
#include <vector>
#include "../ByteAssemble.h"
#include "../Vectors/Vectors.h"
#include "../Pixels.h"

/*    
* Helper for extract pixels from binary buffer. You must to use buffer chunks instead as full one for better perfomance
*/    
namespace WAL
{ //Hello
	namespace PixelExtractors
	{
		template <typename PixelType>
		struct SeparateChannels
		{
			std::vector<PixelType> RedValues;
			std::vector<PixelType> GreenValues;
			std::vector<PixelType> BlueValues;
		};
	}

	namespace Dividers
	{
		typedef std::vector<uint8_t> ByteVector;

		template <typename PixelType>
		class IFormDataForAverage
		{
		public:
			virtual ~IFormDataForAverage() {};
			virtual PixelExtractors::SeparateChannels<PixelType>* Run() = 0;
		};

		template <typename PixelType>
		class SerialDivideForAverage final : public IFormDataForAverage<PixelType>
		{
		public:
			SerialDivideForAverage() = default;

			virtual PixelExtractors::SeparateChannels<PixelType>* Run() override final
			{
				return nullptr;
			}
		};
		template <typename PixelType>
		class AlternatingDivideForAverage final : public IFormDataForAverage<PixelType>
		{
		private:
			const ByteVector& pixelBytes;
			const size_t componentLen;
			const size_t componentCount;

		public:
			AlternatingDivideForAverage(const ByteVector& pixelBytes, const size_t componentLen, const size_t componentCount)
		    :componentCount(componentCount), pixelBytes(pixelBytes), componentLen(componentLen) {};

			virtual PixelExtractors::SeparateChannels<PixelType>* Run() override final
			{
				PixelExtractors::SeparateChannels<PixelType>* channels = new PixelExtractors::SeparateChannels<PixelType>();
				int g = 0;
				for (int i = 0; i < this->componentLen; i++)
				{
					channels.RedValues.at(i) = this->pixelBytes.at(g);
					channels.GreenValues.at(i) = this->pixelBytes.at(g + 1);
					channels.BlueValues.at(i) = this->pixelBytes.at(g + 2);
					g += this->componentCount; //TODO
				}
				return channels;
			}
		};
	}
	namespace PixelExtractors
	{
		typedef Vectors::Vec2 Resolution;
		typedef std::vector<uint8_t> ByteVector;

		/*
		* Extracts pixels from binary buffer
		* @param PixelType Which type of pixel to extract
		*/
		template <typename PixelType>
		class PixelExtractor final
		{
			typedef std::vector<PixelType> PixelVector;

			/*
			* How much one pixel takes byte lenght
			*/
			const size_t pixelSizeInBytes{ 0 };

			/*
			* How many bytes were sended by GetNextPixel(). Commonly for checking next pixel exist
			*/
			size_t handledPixelBytes{ 0 };

			/**
			* It is buffer from where pixel extractor will be extract pixels
			* You can change buffer to new chunk by setbuffer()
			*/
			ByteVector* fileBufferChunk;

			/**
			* Returns row of pixels with lenght as output resolution.X. Ignores some rows be Y step
			* @param step
			* @param maxLen
			*/
			PixelVector GetRow(size_t step, size_t maxLen);


			/**
			* returns true if rows with given length can fit to buffer without empty bytes at the end
			* @param rowLen
			* @param bufLen
			*/
			bool canRowsFitToBuffer(size_t rowLen, size_t bufLen);

			/**
			* Returns nested rows in one 2D array. TODO must return filled rows, for that you need to do right calculation with chunk size in getNextChunk filehandler
			* @param step
			* @param maxLen
			*/
			PixelVector ExtractRow(size_t step, size_t maxLen);

			/*
			* Returns bytes of size of one pixel. TODO create can get pixel bytes
			*/
			ByteVector GetPixelBytes();

			/*
			* Returns channels count of pixel type //TODO should move to pixel type definition? (Pixels.h)
			*/
			constexpr int GetPixelChannelsCount();

			/*
			* How much bytes takes one channel in pixel
			*/
			size_t GetChannelBytesLen();

			PixelVector ConvertFileBufferChunkToPixelVector();

			/*
			* True if pixel types fit file buffer chunk, i.e. no more no less
			*/
			bool canPixelTypesFitBuffer();

		public:
			PixelExtractor() = delete;
			/*
			* @param buffer Buffer to extract from
			* @param pixelSizeInBytes How much one pixel takes bytes
			*/
			PixelExtractor(ByteVector* fileBufferChunk, const size_t pixelSizeInBytes);

			void SetNewBuffer(ByteVector* fileBufferChunk);

			/*
			* Returns pixel while end of buffer is not reached
			* @param outIsNextPixelExist Returns true if next function call will give valid pixel
			*/
			PixelType GetNextPixel(bool& outIsNextPixelExist);

			bool canGetNextPixel();

		};

		template<typename PixelType>
		inline PixelExtractor<PixelType>::PixelExtractor(ByteVector* fileBufferChunk, const size_t pixelSizeInBytes) : fileBufferChunk(fileBufferChunk)
		{
		}

		template <typename PixelType>
		inline std::vector<PixelType> PixelExtractor<PixelType>::ExtractRow(size_t step, size_t maxLen)
		{
		}

		template <typename PixelType>
		inline std::vector<PixelType> PixelExtractor<PixelType>::GetRow(size_t step, size_t maxLen)
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
			//TEMPLATE
			ByteVector vec(pixelSizeInBytes);
			for (int i = 0; i < pixelSizeInBytes; i++)
			{
				vec.at(i) = fileBufferChunk->at(i);
			}

			return vec;
			//get n bytes from array. how much to take calculates by dirRes / outputRes 
			//return ByteAssemble::DEPRECATED_GetBytesFrom<this->pixelSizeInBytes>(this->buffer); //TODO chanke from template to common func
		}

		template<typename PixelType>
		inline constexpr int PixelExtractor<PixelType>::GetPixelChannelsCount()
		{
			return 3;
		}

		template<typename PixelType>
		inline size_t PixelExtractor<PixelType>::GetChannelBytesLen()
		{
			return (size_t)std::floor(this->pixelSizeInBytes / this->GetPixelChannelsCount());
		}

		template<typename PixelType>
		inline std::vector<PixelType> PixelExtractor<PixelType>::ConvertFileBufferChunkToPixelVector()
		{
			if (canPixelTypesFitBuffer())
			{
				PixelVector pixels;
				const auto pixelCount = fileBufferChunk->size() / sizeof(PixelType);

				//convert group of bytes to pixels
				for (int i = 0; i < pixelCount; i++)
				{
					std::array<uint8_t, sizeof(PixelType)> RawPixel;
					int g = 0;
					for (int j = 0; j < sizeof(PixelType); j++)
					{
						RawPixel[j] = fileBufferChunk->at(g + j);
						g += sizeof(PixelType);
					}
					auto pixel = ByteAssemble::GlueBytesToChannel<PixelType>(RawPixel);
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
			return (fileBufferChunk->size() % sizeof(PixelType)) == 0;
		}

		template<typename PixelType>
		inline void PixelExtractor<PixelType>::SetNewBuffer(ByteVector* fileBufferChunk)
		{
			this->fileBufferChunk = fileBufferChunk;
		}

		template<typename PixelType>
		inline PixelType PixelExtractor<PixelType>::GetNextPixel(bool& outIsNextPixelExist)
		{
			if (!this->fileBufferChunk)
			{
				outIsNextPixelExist = false;
				return PixelType();
			}

			if (this->pixelSizeInBytes == 0)
			{
				outIsNextPixelExist = false;
				return PixelType(); //TODO through exception
			}

			if (canGetNextPixel())
			{
				auto pixelBytes = GetPixelBytes();
				auto channelLen = GetChannelBytesLen();
				PixelVector pixels = ConvertFileBufferChunkToPixelVector();

				PixelVector RedPixels(channelLen);
				PixelVector GreenPixels(channelLen);
				PixelVector BluePixels(channelLen);

				Dividers::IFormDataForAverage<PixelType>* getForAverage = Dividers::AlternatingDivideForAverage<PixelType>(pixelBytes, channelLen, 3); //TODO delete
				SeparateChannels* channels = getForAverage->Run(); //TODO delete

				//get average in each chunk
				PixelType R = ByteAssemble::GetAverageFrom<PixelType>(*channels.RedValues, channelLen);
				PixelType G = ByteAssemble::GetAverageFrom<PixelType>(*channels.GreenValues, channelLen);
				PixelType B = ByteAssemble::GetAverageFrom<PixelType>(*channels.BlueValues, channelLen);
				//save average to 3 component of pixel
				this->handledPixelBytes += this->pixelSizeInBytes;
				outIsNextPixelExist = canGetNextPixel();
				return PixelType(R, G, B);
			}
			else
			{
				outIsNextPixelExist = false;
			}
		
		}
		template<typename PixelType>
		inline bool PixelExtractor<PixelType>::canGetNextPixel()
		{
			return !((handledPixelBytes + pixelSizeInBytes) > fileBufferChunk->size());
		}
	}
}