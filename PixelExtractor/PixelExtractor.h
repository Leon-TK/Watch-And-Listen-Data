#pragma once
#include <fstream>
#include <vector>
#include "../ByteAssemble.h"
#include "../Vectors/Vectors.h"

/*    
* Helper for extract pixels from binary buffer. You must to use buffer chunks instead as full one for better perfomance
*/    
namespace WAL
{
	namespace Pixels
	{
		template <typename ChannelType>
		class TRgbPixel final
		{
			Vectors::TVec3<ChannelType> channels;
		};
		template <typename ChannelType>
		class TRgbaPixel final
		{
			Vectors::TVec3<ChannelType> channels;
			ChannelType alpha;
		};
		template <typename ChannelType>
		class TMonoPixel final
		{
			ChannelType channel;
		};

		class RgbPixel final
		{
			Vectors::TVec3<uint8_t> channels;
		};

		class RgbaPixel final
		{
			Vectors::TVec3<uint8_t> channels;
			uint8_t alpha;
		};

		class MonoPixel final
		{
			uint8_t channel;
		};
	}

	namespace Dividers
	{
		template <typename>
		struct SparseChannels;

		template <typename ChannelType>
		class IFormDataForAverage
		{
		public:
			virtual ~IFormDataForAverage() {};
			virtual SparseChannels<ChannelType>* Run(ByteVector& pixelBytes, size_t componentLen) = 0;
		};

		template <typename ChannelType>
		class SerialDivideForAverage final : public IFormDataForAverage<ChannelType>
		{
		public:
			SerialDivideForAverage() = default;

			virtual SparseChannels<ChannelType>* Run(ByteVector& pixelBytes, size_t componentLen) override final
			{
				return nullptr;
			}
		};
		template <typename ChannelType>
		class AlternatingDivideForAverage final : public IFormDataForAverage<ChannelType>
		{
		public:
			AlternatingDivideForAverage() = default;

			virtual SparseChannels<ChannelType>* Run(ByteVector& pixelBytes, size_t componentLen) override final
			{
				SparseChannels<ChannelType>* channels = new SparseChannels<ChannelType>();
				int g = 0;
				for (int i = 0; i < componentLen; i++)
				{
					channels.RedValues.at(i) = pixelBytes.at(g);
					channels.GreenValues.at(i) = pixelBytes.at(g + 1);
					channels.BlueValues.at(i) = pixelBytes.at(g + 2);
					g += GetPixelComponentCount(); //TODO
				}
				return channels;
			}
		};
	}
	namespace PixelExtractors
	{
		typedef Pixels::TRgbPixel<uint16_t> Pixel;
		typedef Vectors::Vec2 Resolution;
		typedef std::vector<uint8_t> ByteVector;
		typedef std::vector<Pixel> PixelVector;
		/*template <typename T>
		class Vec3;
		template <typename T>
		class Vec2;*/

		/*
		* Extracts pixels from binary buffer
		* @param ChannelType Which type of pixel to extract
		*/
		template <typename ChannelType>
		class PixelExtractor final
		{
			template <typename ChannelType>
			struct SparseChannels
			{
				PixelVector RedValues;
				PixelVector GreenValues;
				PixelVector BlueValues;
			};

			const size_t pixelSizeInBytes{ 0 };

			/**
			* You can change buffer to new chunk by setbuffer()
			*/
			ByteVector* buffer;

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

			ByteVector GetPixelBytes();

			constexpr int GetPixelComponentCount();

			size_t GetComponentBytesLen();

			PixelVector ConvertComponentBytesToPixels();

			bool canPixelTypesFitBuffer();

		public:
			PixelExtractor() = delete;
			PixelExtractor(ByteVector* buffer, const size_t pixelSizeInBytes);

			void SetNewBuffer(ByteVector* buffer);

			/*
			* Returns pixel while end of buffer is not reached
			*/
			Pixel GetNextPixel(bool& outIsNextPixelExist);

			bool canGetNextPixel();

		};

		template<typename ChannelType>
		inline PixelExtractor<ChannelType>::PixelExtractor(ByteVector* buffer, const size_t pixelSizeInBytes) : buffer(buffer)
		{
		}

		template <typename ChannelType>
		inline PixelVector PixelExtractor<ChannelType>::ExtractRow(size_t step, size_t maxLen)
		{
		}

		template <typename ChannelType>
		inline PixelVector PixelExtractor<ChannelType>::GetRow(size_t step, size_t maxLen)
		{
		}

		template <typename ChannelType>
		inline bool PixelExtractor<ChannelType>::canRowsFitToBuffer(size_t rowLen, size_t bufLen)
		{
			return (bufLen % rowLen) == 0;
		}

		template<typename ChannelType>
		inline std::vector<uint8_t> PixelExtractor<ChannelType>::GetPixelBytes()
		{
			//get n bytes from array. how much to take calculates by dirRes / outputRes 
			return ByteAssemble::DEPRECATED_GetBytesFrom<this->pixelSizeInBytes>(this->buffer); //TODO chanke from template to common func
		}

		template<typename ChannelType>
		inline constexpr int PixelExtractor<ChannelType>::GetPixelComponentCount()
		{
			return 3;
		}

		template<typename ChannelType>
		inline size_t PixelExtractor<ChannelType>::GetComponentBytesLen()
		{
			return (size_t)std::floor(this->pixelSizeInBytes / this->GetPixelComponentCount());
		}

		template<typename ChannelType>
		inline PixelVector PixelExtractor<ChannelType>::ConvertComponentBytesToPixels()
		{
			if (canPixelTypesFitBuffer())
			{
				PixelVector pixels;
				const auto pixelCount = buffer->size() / sizeof(ChannelType);

				//convert group of bytes to pixels
				for (int i = 0; i < pixelCount; i++)
				{
					std::array<uint8_t, sizeof(ChannelType)> RawPixel;
					int g = 0;
					for (int j = 0; j < sizeof(ChannelType); j++)
					{
						RawPixel[j] = buffer->at(g + j);
						g += sizeof(ChannelType);
					}
					auto pixel = ByteAssemble::GlueBytes<sizeof(ChannelType)>(RawPixel);
					pixels.push_back(pixel);
				}

				return pixels;
			}
			else
			{
				return PixelVector(0);
			}

		}

		template<typename ChannelType>
		inline bool PixelExtractor<ChannelType>::canPixelTypesFitBuffer()
		{
			return (buffer->size() % sizeof(ChannelType)) == 0;
		}

		template<typename ChannelType>
		inline void PixelExtractor<ChannelType>::SetNewBuffer(ByteVector* buffer)
		{
			this->buffer = buffer;
		}

		template<typename ChannelType>
		inline Pixel PixelExtractor<ChannelType>::GetNextPixel(bool& outIsNextPixelExist)
		{
			if (!this->buffer)
			{
				outIsNextPixelExist = false;
				return Pixel();
			}

			if (this->pixelSizeInBytes == 0)
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

			Dividers::IFormDataForAverage<ChannelType>* getForAverage = Dividers::AlternatingDivideForAverage<ChannelType>();
			SparseChannels* channels = getForAverage->Run(pixelBytes);

			//get average in each chunk
			ChannelType R = ByteAssemble::GetAverageFrom<ChannelType>(*channels.RedValues, componentLen);
			ChannelType G = ByteAssemble::GetAverageFrom<ChannelType>(*channels.GreenValues, componentLen);
			ChannelType B = ByteAssemble::GetAverageFrom<ChannelType>(*channels.BlueValues, componentLen);
			//save average to 3 component of pixel
			//set new current position 
			return Pixel(R, G, B);
		}
		template<typename ChannelType>
		inline bool PixelExtractor<ChannelType>::canGetNextPixel()
		{
			return false;
		}
	}
}