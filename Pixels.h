#pragma once
#include "Vectors/Vectors.h"
namespace WAL
{
	namespace Pixels
	{

		template <typename ChannelType>
		struct TRgbPixel final
		{
			WAL::Vectors::TVec3<ChannelType> channels;
			typedef ChannelType channelType;
			static constexpr uint8_t GetChannelsCount()
			{
				return 3;
			}
		};
		template <typename ChannelType>
		struct TRgbaPixel final
		{
			WAL::Vectors::TVec3<ChannelType> channels;
			ChannelType alpha;
			typedef ChannelType channelType;
			static constexpr uint8_t GetChannelsCount()
			{
				return 4;
			}
		};
		template <typename ChannelType>
		struct TMonoPixel final
		{
			ChannelType channel;
			typedef ChannelType channelType;
			static constexpr uint8_t GetChannelsCount()
			{
				return 1;
			}
		};

		struct RgbPixel final
		{
			WAL::Vectors::TVec3<uint8_t> channels;
			static constexpr uint8_t GetChannelsCount()
			{
				return 3;
			}
		};

		struct RgbaPixel final
		{
			WAL::Vectors::TVec3<uint8_t> channels;
			uint8_t alpha;
			static constexpr uint8_t GetChannelsCount()
			{
				return 4;
			}
		};

		struct MonoPixel final
		{
			uint8_t channel;
			static constexpr uint8_t GetChannelsCount()
			{
				return 1;
			}
		};
	}
}
