#pragma once
/*    
* template class
*/
namespace WAL
{
	namespace Vectors
	{
		template<typename T>
		struct TVec2
		{
			TVec2() : x(0), y(0) {};
			TVec2(const T x, const T y) : x(x), y(y) {};
			T x;
			T y;

			const TVec2 operator=(const TVec2& rhs)
			{
				return TVec2(rhs.x, rhs.y);
			}

			typedef T type;
		};
		template<typename T>
		struct TVec3
		{
			TVec3() : x(0), y(0), z(0) {};
			TVec3(const T x, const T y, const T z) : x(x), y(y), z(z) {};
			T x;
			T y;
			T z;

			const TVec3 operator=(const TVec3& rhs)
			{
				return TVec3(rhs.x, rhs.y, rhs.z);
			}

			typedef T type;
		};

		struct Vec2
		{
			uint32_t x;
			uint32_t y;
			
			Vec2() : x(0), y(0) {};
			Vec2(const uint32_t x, const uint32_t y): x(x), y(y) {};

			const Vec2 operator=(const Vec2& rhs)
			{
				return Vec2(rhs.x, rhs.y);
			}

		};

		struct Vec3
		{
			uint32_t x;
			uint32_t y;
			uint32_t z;

			Vec3() : x(0), y(0), z(0) {};
			Vec3(const uint32_t x, const uint32_t y, const uint32_t z) : x(x), y(y), z(z) {};

			const Vec3 operator=(const Vec3& rhs)
			{
				return Vec3(rhs.x, rhs.y, rhs.z);
			}

		};
	}
}