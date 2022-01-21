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
		template <typename ChannelType>
		struct SeparateChannels
		{
			std::vector<ChannelType> RedValues;
			std::vector<ChannelType> GreenValues;
			std::vector<ChannelType> BlueValues;
		};
	}

	namespace Dividers
	{
		typedef std::vector<uint8_t> ByteVector;

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
			const ByteVector& pixelBytes;
			const size_t componentLen;
			const size_t componentCount;

		public:
			AlternatingDivideForAverage(const ByteVector& pixelBytes, const size_t componentLen, const size_t componentCount)
		    :componentCount(componentCount), pixelBytes(pixelBytes), componentLen(componentLen) {};

			virtual PixelExtractors::SeparateChannels<ChannelType>* Run() override final
			{
				PixelExtractors::SeparateChannels<ChannelType>* channels = new PixelExtractors::SeparateChannels<ChannelType>();
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
		* It's chunk of bytes that must be converted to Pixel
		*/
		struct PixelChunk
		{
			ByteVector bytes;
			PixelChunk(ByteVector bytes) : bytes(bytes) {};
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
			size_t handledPixelBytes{ 0 };

			/**
			* It will be converted to pixel vector
			* You can change buffer to new chunk by setbuffer()
			*/
			ByteVector* fileBufferChunk;

			/*
			* Vector to extract pixels from.
			* 
			* Converted fileBufferChunk.
			*/
			PixelVector* rawPixelBuffer;

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
			* Returns bytes of size of one pixel. TODO create can get pixel bytes //2 TODO must track how much bytes was taken
			*/
			PixelChunk GetNextPixelChunk(bool& outIsNextChunkExist);
			bool isNextPixelChunkExist();

			/*
			* Returns channels count of pixel type //TODO should move to pixel type definition? (Pixels.h)
			*/
			constexpr int GetPixelChannelsCount();

			/*
			* How much bytes takes one channel in pixel
			*/
			size_t GetChannelLenInBytes();

			PixelType ConvertPixelChunkToPixel(PixelChunk& pixelChunk);
			SeparateChannels<uint8_t> ConvertPixelChunkToChannels(PixelChunk& pixelChunk); //TODO uint8_t must be user defined ChannelType 
			/*
			* True if pixel types fit file buffer chunk, i.e. no more no less
			*/
			bool canPixelTypesFitBuffer(); //1

			PixelType GetPixelFrom(SeparateChannels<uint8_t>& separateChannels);

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
		inline PixelChunk PixelExtractor<PixelType>::GetNextPixelChunk(bool& outIsNextChunkExist)
		{
			if (isNextPixelChunkExist())
			{
				ByteVector vec(pixelSizeInBytes);
				for (int i = 0; i < pixelSizeInBytes; i++)
				{
					vec.at(i) = fileBufferChunk->at(i); //TODO get bext ...
				}
				this->handledPixelBytes += this->pixelSizeInBytes;
				outIsNextChunkExist = isNextPixelChunkExist();
				return PixelChunk(vec);
			}
			else
			{
				//throw error
				outIsNextChunkExist = false;
				return PixelChunk(ByteVector(0));
			}
		}

		template<typename PixelType>
		inline bool PixelExtractor<PixelType>::isNextPixelChunkExist()
		{
			if (this->handledPixelBytes + this->pixelSizeInBytes > this->fileBufferChunk->size()) return false; else return true;
		}

		template<typename PixelType>
		inline constexpr int PixelExtractor<PixelType>::GetPixelChannelsCount()
		{
			return 3;
		}

		template<typename PixelType>
		inline size_t PixelExtractor<PixelType>::GetChannelLenInBytes()
		{
			return (size_t)std::floor(this->pixelSizeInBytes / this->GetPixelChannelsCount());
		}

		template<typename PixelType>
		inline PixelType PixelExtractor<PixelType>::ConvertPixelChunkToPixel(PixelChunk& pixelChunk) //TODO redo this shit
		{
			SeparateChannels channels = ConvertPixelChunkToChannels(pixelChunk);
			return this->GetPixelFrom(channels);
	

			////old
			//if (canPixelTypesFitBuffer())
			//{
			//	PixelVector pixels;
			//	const auto pixelCount = fileBufferChunk->size() / sizeof(PixelType);

			//	//convert group of bytes to pixels
			//	for (int i = 0; i < pixelCount; i++)
			//	{
			//		std::array<uint8_t, sizeof(PixelType)> RawPixel;
			//		int g = 0;
			//		for (int j = 0; j < sizeof(PixelType); j++)
			//		{
			//			RawPixel[j] = fileBufferChunk->at(g + j);
			//			g += sizeof(PixelType);
			//		}
			//		auto pixel = ByteAssemble::GlueBytesToChannel<PixelType>(RawPixel);
			//		pixels.push_back(pixel);
			//	}

			//	return pixels;
			//}
			//else
			//{
			//	return PixelVector(0);
			//}
			////~old

		}
		template<typename PixelType>
		inline SeparateChannels<uint8_t> PixelExtractor<PixelType>::ConvertPixelChunkToChannels(PixelChunk& pixelChunk) //TODO redo this shit
		{

			Dividers::ICreateSeparateChannels<uint8_t>* getSeparateChannels = Dividers::AlternatingDivideForAverage<uint8_t>(pixelChunk, GetChannelLenInBytes(), 3); 
			auto result = getSeparateChannels->Run();
			delete getSeparateChannels;
			return result; 

			//if (canPixelTypesFitBuffer())
			//{
			//	PixelVector pixels;
			//	const auto pixelCount = fileBufferChunk->size() / sizeof(PixelType);

			//	//convert group of bytes to pixels
			//	for (int i = 0; i < pixelCount; i++)
			//	{
			//		std::array<uint8_t, sizeof(PixelType)> RawPixel;
			//		int g = 0;
			//		for (int j = 0; j < sizeof(PixelType); j++)
			//		{
			//			RawPixel[j] = fileBufferChunk->at(g + j);
			//			g += sizeof(PixelType);
			//		}
			//		auto pixel = ByteAssemble::GlueBytesToChannel<PixelType>(RawPixel);
			//		pixels.push_back(pixel);
			//	}

			//	return pixels;
			//}
			//else
			//{
			//	return PixelVector(0);
			//}

		}

		template<typename PixelType>
		inline bool PixelExtractor<PixelType>::canPixelTypesFitBuffer()
		{
			return (fileBufferChunk->size() % sizeof(PixelType)) == 0; //TODO huyna?
		}

		template<typename PixelType>
		inline PixelType PixelExtractor<PixelType>::GetPixelFrom(SeparateChannels<uint8_t>& separateChannels)
		{

			//old
			uint8_t R = ByteAssemble::GetAverageFrom<uint8_t>(separateChannels.RedValues, GetChannelLenInBytes()); //TODO channeltype instead of pixeltype
			uint8_t G = ByteAssemble::GetAverageFrom<uint8_t>(separateChannels.GreenValues, GetChannelLenInBytes());
			uint8_t B = ByteAssemble::GetAverageFrom<uint8_t>(separateChannels.BlueValues, GetChannelLenInBytes());
			//~old

			PixelType pixel;
			pixel.channels.at(0) = R;
			pixel.channels.at(1) = G;
			pixel.channels.at(2) = B;

			return pixel;
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
				bool isNextExist = true;
				auto pixelChunk = GetNextPixelChunk(isNextExist);
				outIsNextPixelExist = isNextExist;

				auto channelLen = GetChannelLenInBytes();
				auto pixel = ConvertPixelChunkToPixel(pixelChunk);
	
				this->handledPixelBytes += this->pixelSizeInBytes;

				return pixel;
			}
			else
			{
				outIsNextPixelExist = false;
			}
		
		}
		template<typename PixelType>
		inline bool PixelExtractor<PixelType>::canGetNextPixel()
		{
			return this->isNextPixelChunkExist();
		}
	}
}