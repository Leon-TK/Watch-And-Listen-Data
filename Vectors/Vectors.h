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
				return TVec3(rhs.x, rhs.y, ths.z);
			}
		};
	}
}