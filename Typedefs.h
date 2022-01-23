#pragma once
#include <vector>

namespace WAL
{
	namespace Vectors
	{
		template <typename>
		struct TVec2;
	}

	typedef Vectors::TVec2<uint16_t> Resolution_t;
	typedef std::vector<uint8_t> ByteVector_t;

}