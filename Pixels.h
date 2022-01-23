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
		};
		template <typename ChannelType>
		struct TRgbaPixel final
		{
			WAL::Vectors::TVec3<ChannelType> channels;
			ChannelType alpha;
			typedef ChannelType channelType;
		};
		template <typename ChannelType>
		struct TMonoPixel final
		{
			ChannelType channel;
			typedef ChannelType channelType;
		};

		struct RgbPixel final
		{
			WAL::Vectors::TVec3<uint8_t> channels;
		};

		struct RgbaPixel final
		{
			WAL::Vectors::TVec3<uint8_t> channels;
			uint8_t alpha;
		};

		struct MonoPixel final
		{
			uint8_t channel;
		};
	}
}
