#ifndef _GEN_VECTOR_H_INCLUDED_
#define _GEN_VECTOR_H_INCLUDED_

namespace Cog
{
	namespace Generics
	{
		template <typename F> class Vector
		{
		public:
			F X, Y, Z;

			Vector()
				: X(0), Y(0), Z(0)
			{
				return;
			}

			Vector(F x, F y, F z)
				: X(x), Y(y), Z(z)
			{
				return;
			}

			Vector(const Vector& v)
			{
				*this = v;
			}

			const Vector& operator=(const Vector& v)
			{
				X = v.X;
				Y = v.Y;
				Z = v.Z;

				return v;
			}

			bool operator==(const Vector& v) const
			{
				return X == v.X && Y == v.Y && Z == v.Z;
			}
		};
	}
}

#endif // _GEN_VECTOR_H_INCLUDED_
