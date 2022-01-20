/*    
* template class
*/
namespace WAL
{
	template <typename T>
	class Vec2
	{
	public:
		Vec2() = default;
		Vec2(T x, T y) : X(x), Y(y) {};
		
		T X;
		T Y;

		const Vec2 operator=(const Vec2& rhs)
		{
			Vec2 New;
			New.X = rhs.X;
			New.Y = rhs.Y;

			return New;
		}
	};
}