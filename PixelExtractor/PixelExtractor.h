#pragma once
#include <fstream>
#include <vector>
#include "../ByteAssemble.h"
#include "../Vectors/Vectors.h"
#include "../Pixels.h"
#include "../Typedefs.h"
#include "../Exceptions.h"
/*    
* Helper for extract pixels from binary buffer. You must to use buffer chunks instead as full one for better perfomance
*/    
namespace WAL
{
	namespace PixelExtractors
	{
		template <typename>
		struct SeparateChannels;
	};

	namespace Dividers
	{

		template <typename ChannelType>
		class ICreateSeparateChannels
		{
		public:
			virtual ~ICreateSeparateChannels() {};
			virtual PixelExtractors::SeparateChannels<ChannelType>* Run() = 0;
		};

		template <typename ChannelType>
		class SerialDivideForAverage final : public ICreateSeparateChannels<ChannelType>
		{
		public:
			SerialDivideForAverage() = default;

			virtual PixelExtractors::SeparateChannels<ChannelType>* Run() override final
			{
				return nullptr;
			}
		};
		template <typename ChannelType>
		class AlternatingDivideForAverage final : public ICreateSeparateChannels<ChannelType>
		{
		private:
			const ByteVector_t& pixelBytes;
			const size_t componentLen;
			const size_t componentCount;

		public:
			AlternatingDivideForAverage(const ByteVector_t& pixelBytes, const size_t componentLen, const size_t componentCount)
		    :componentCount(componentCount), pixelBytes(pixelBytes), componentLen(componentLen) {};

			virtual PixelExtractors::SeparateChannels<ChannelType>* Run() override final
			{
				PixelExtractors::SeparateChannels<ChannelType>* channels = new PixelExtractors::SeparateChannels<ChannelType>();
				size_t g = 0;
				for (int i = 0; i < this->componentLen; i++)
				{
					channels->RedValues.at(i) = this->pixelBytes.at(g);
					channels->GreenValues.at(i) = this->pixelBytes.at(g + 1);
					channels->BlueValues.at(i) = this->pixelBytes.at(g + 2);
					g += this->componentCount; //TODO
				}
				return channels;
			}
		};
	}
	namespace PixelExtractors
	{
		template <typename ChannelType>
		struct SeparateChannels
		{
			std::vector<ChannelType> RedValues;
			std::vector<ChannelType> GreenValues;
			std::vector<ChannelType> BlueValues;
		};

		/*
		* It's chunk of bytes that must be converted to Pixel
		*/
		struct PixelChunk
		{
			ByteVector_t bytes;
			PixelChunk(ByteVector_t bytes) : bytes(bytes) {};
			PixelChunk() = delete;
		};

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
			size_t processeddPixelBytes{ 0 };

			/**
			* It will be converted to pixel vector
			* You can change buffer to new chunk by setbuffer()
			*/
			ByteVector_t* fileBufferChunk;

			/*
			* Vector to extract pixels from.
			* 
			* Converted fileBufferChunk.
			*/
			PixelVector* rawPixelBuffer{nullptr}; //UNUSED

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

			//TODO must return filled rows, for that you need to do right calculation with chunk size in getNextChunk filemanager
			/**
			* Returns nested rows in one 2D array. 
			* @param step
			* @param maxLen
			*/
			PixelVector ExtractRow(size_t step, size_t maxLen);

			/*
			* Returns bytes of size of one pixel. 
			*/
			PixelChunk GetNextPixelChunk(bool& outIsNextChunkExist);
			bool isNextPixelChunkExist();

			//TODO should move to pixel type definition? (Pixels.h)
			/*
			* Returns channels count of pixel type 
			*/
			constexpr int GetPixelChannelsCount();

			/*
			* How much bytes takes one channel in pixel
			*/
			size_t GetChannelLenInBytes();

			PixelType ConvertPixelChunkToPixel(PixelChunk& pixelChunk);
			SeparateChannels<typename PixelType::channelType> ConvertPixelChunkToChannels(PixelChunk& pixelChunk);
			/*
			* True if pixel types fit file buffer chunk, i.e. no more no less
			*/
			bool canPixelTypesFitBuffer(); //1

			PixelType GetPixelFrom(SeparateChannels<typename PixelType::channelType>& separateChannels);

		public:
			typedef std::vector<PixelType> PixelVector;

			PixelExtractor() = delete;
			/*
			* @param buffer Buffer to extract from
			* @param pixelSizeInBytes How much one pixel takes bytes
			*/
			PixelExtractor(ByteVector_t* fileBufferChunk, const size_t pixelSizeInBytes);

			void SetNewBuffer(ByteVector_t* fileBufferChunk);

			/*
			* Returns pixel while end of buffer is not reached
			* @param outIsNextPixelExist Returns true if next function call will give valid pixel
			*/
			PixelType GetNextPixel(bool& outIsNextPixelExist);

			bool canGetNextPixel();

		};

		template<typename PixelType>
		inline PixelExtractor<PixelType>::PixelExtractor(ByteVector_t* fileBufferChunk, const size_t pixelSizeInBytes) : fileBufferChunk(fileBufferChunk)
		{
		}

		template <typename PixelType>
		inline PixelExtractor<PixelType>::PixelVector PixelExtractor<PixelType>::ExtractRow(size_t step, size_t maxLen)
		{
		}

		template <typename PixelType>
		inline PixelExtractor<PixelType>::PixelVector PixelExtractor<PixelType>::GetRow(size_t step, size_t maxLen)
		{
		}

		template <typename PixelType>
		inline bool PixelExtractor<PixelType>::canRowsFitToBuffer(size_t rowLen, size_t bufLen)
		{
			return (bufLen % rowLen) == 0;
		}

		template<typename PixelType>
		inline PixelChunk PixelExtractor<PixelType>::GetNextPixelChunk(bool& outIsNextChunkExist)
		{
			if (isNextPixelChunkExist())
			{
				ByteVector_t vec(pixelSizeInBytes);
				for (int i = 0; i < pixelSizeInBytes; i++)
				{
					vec.at(i) = fileBufferChunk->at(i); //TODO get bext ...
				}
				this->processeddPixelBytes += this->pixelSizeInBytes;
				outIsNextChunkExist = isNextPixelChunkExist();
				return PixelChunk(vec);
			}
			else
			{
				throw Exceptions::NextNotExist();
			}
		}

		template<typename PixelType>
		inline bool PixelExtractor<PixelType>::isNextPixelChunkExist()
		{
			if (this->processeddPixelBytes + this->pixelSizeInBytes > this->fileBufferChunk->size()) return false; else return true;
		}

		template<typename PixelType>
		inline constexpr int PixelExtractor<PixelType>::GetPixelChannelsCount()
		{
			return 3;
		}

		template<typename PixelType>
		inline size_t PixelExtractor<PixelType>::GetChannelLenInBytes()
		{
			return (size_t)std::floor(this->pixelSizeInBytes / PixelType::GetChannelsCount());
		}

		template<typename PixelType>
		inline PixelType PixelExtractor<PixelType>::ConvertPixelChunkToPixel(PixelChunk& pixelChunk)
		{
			SeparateChannels channels = ConvertPixelChunkToChannels(pixelChunk);
			return this->GetPixelFrom(channels);

		}
		template<typename PixelType>
		inline SeparateChannels<typename PixelType::channelType> PixelExtractor<PixelType>::ConvertPixelChunkToChannels(PixelChunk& pixelChunk)
		{

			Dividers::ICreateSeparateChannels<typename PixelType::channelType>* getSeparateChannels = new Dividers::AlternatingDivideForAverage<typename PixelType::channelType>(pixelChunk.bytes, GetChannelLenInBytes(), 3);
			auto resultPtr = getSeparateChannels->Run();
			auto result = *resultPtr;
			delete getSeparateChannels;
			delete resultPtr;
			return result; 

		}

		template<typename PixelType>
		inline bool PixelExtractor<PixelType>::canPixelTypesFitBuffer()
		{
			return (fileBufferChunk->size() % sizeof(PixelType)) == 0; //TODO huyna?
		}

		template<typename PixelType>
		inline PixelType PixelExtractor<PixelType>::GetPixelFrom(SeparateChannels<typename PixelType::channelType>& separateChannels)
		{
			typename PixelType::channelType R = ByteAssemble::GetAverageFrom<typename PixelType::channelType>(separateChannels.RedValues, GetChannelLenInBytes());
			typename PixelType::channelType G = ByteAssemble::GetAverageFrom<typename PixelType::channelType>(separateChannels.GreenValues, GetChannelLenInBytes());
			typename PixelType::channelType B = ByteAssemble::GetAverageFrom<typename PixelType::channelType>(separateChannels.BlueValues, GetChannelLenInBytes());

			PixelType pixel;
			pixel.channels.x = R;
			pixel.channels.y = G;
			pixel.channels.z = B;

			return pixel;
		}

		template<typename PixelType>
		inline void PixelExtractor<PixelType>::SetNewBuffer(ByteVector_t* fileBufferChunk)
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
				throw Exceptions::NextNotExist();
			}

			if (canGetNextPixel())
			{
				bool isNextExist = true;
				auto pixelChunk = GetNextPixelChunk(isNextExist);
				outIsNextPixelExist = isNextExist;

				auto channelLen = GetChannelLenInBytes();
				auto pixel = ConvertPixelChunkToPixel(pixelChunk);
	
				this->processeddPixelBytes += this->pixelSizeInBytes;

				return pixel;
			}
			else
			{
				throw Exceptions::NextNotExist();
			}
		
		}
		template<typename PixelType>
		inline bool PixelExtractor<PixelType>::canGetNextPixel()
		{
			return this->isNextPixelChunkExist();
		}
	}
}