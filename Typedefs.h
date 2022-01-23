#pragma once
#include <vector>
#include "Vectors/Vectors.h"

namespace WAL
{
	namespace Vectors
	{
		template <typename>
		struct TVec2;
	}

	typedef uint16_t ResolutionType;
	typedef Vectors::TVec2<uint16_t> Resolution_t;
	typedef std::vector<uint8_t> ByteVector_t;

}