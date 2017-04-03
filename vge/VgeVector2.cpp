#include "Vge.h"

namespace Vge
{
	Vector2::Vector2() {}

	Vector2::Vector2(float _x, float _y)
		: x(_x), y(_y) {}

	float Vector2::SquareLength() const
	{
		return x*x + y*y;
	}
	float Vector2::Length() const
	{
		return Math::Sqrt(x*x + y*y);
	}

	float Vector2::Normalize()
	{
		float length = Length();

		if ( length > 1e-06f )
		{
			float invlen = 1.0f / length;

			x *= invlen;
			y *= invlen;
		}
		else
		{
			x = 0.0f;
			y = 0.0f;

			length = 0.0f;
		}

		return length;
	}

	Vector2 Vector2::operator + ( float dis ) const
	{
		return Vector2(x+dis, y+dis);
	}

	Vector2 Vector2::operator + ( const Vector2& rhs ) const
	{
		return Vector2(x+rhs.x, y+rhs.y);
	}

	Vector2& Vector2::operator += ( float dis )
	{
		x+=dis;
		y+=dis;
		return *this;
	}

	Vector2 Vector2::operator - ( float dis ) const
	{
		return Vector2(x-dis, y-dis);
	}

	Vector2 Vector2::operator - ( const Vector2& rhs ) const
	{
		return Vector2(x-rhs.x, y-rhs.y);
	}

	Vector2& Vector2::operator -= ( float dis )
	{
		x-=dis;
		y-=dis;
		return *this;
	}

	Vector2 Vector2::operator * ( float n ) const
	{
		return Vector2(x*n, y*n);
	}

	Vector2 Vector2::operator * ( const Vector2& rhs ) const
	{
		return Vector2(x*rhs.x, y*rhs.y);
	}

	Vector2& Vector2::operator *= ( float n )
	{
		x*=n;
		y*=n;
		return *this;
	}

	Vector2 Vector2::operator / ( float n ) const
	{
		float invn = 1.0f / n;
		return Vector2(x*invn, y*invn);
	}

	Vector2& Vector2::operator /= ( float n )
	{
		float invn = 1.0f / n;
		x*=invn;
		y*=invn;
		return *this;
	}
}