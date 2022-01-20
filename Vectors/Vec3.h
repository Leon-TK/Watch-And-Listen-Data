/*    
* template class
*/
namespace WAL
{
	template <typename T>
	class Vec3
	{
	public:
		Vec3() = default;
		Vec3(T x, T y, T z) : X(x), Y(y), Z(z) {};
		T X;
		T Y;
		T Z;
		const Vec3 operator=(const Vec3& rhs)
		{
			Vec3 New;
			New.X = rhs.X;
			New.Y = rhs.Y;
			New.Z = rhs.Z;

			return New;
		}

	};
}