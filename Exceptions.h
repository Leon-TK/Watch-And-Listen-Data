#pragma once
#include <exception>

namespace Exceptions
{
	class AspectRatioNotFound : public std::exception {};
	class PixelsNotFit : public std::exception {};
	class ChunkExceedesRam: public std::exception{};
	class NextNotExist : public std::exception {};
}