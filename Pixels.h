#pragma once

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