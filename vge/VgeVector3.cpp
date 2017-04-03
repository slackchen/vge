#include "Vge.h"

namespace Vge
{
	const Vector3 Vector3::ZERO = Vector3( 0.0f, 0.0f, 0.0f );
	const Vector3 Vector3::UNIT_X = Vector3( 1.0f, 0.0f, 0.0f );
	const Vector3 Vector3::UNIT_Y = Vector3( 0.0f, 1.0f, 0.0f );
	const Vector3 Vector3::UNIT_Z = Vector3( 0.0f, 0.0f, 1.0f );
	const Vector3 Vector3::UNIT_ALL = Vector3( 1.0f, 1.0f, 1.0f );

	Vector3::Vector3()
	{
	}

	Vector3::Vector3( float _x, float _y, float _z )
		: x( _x ), y( _y ), z( _z )
	{
	}

	Vector3::Vector3( const Vector3& rhs )
	{
		*this = rhs;
	}

	Vector3 Vector3::Cross( const Vector3& rhs ) const
	{
		return Vector3( y*rhs.z - z*rhs.y, x*rhs.z - z*rhs.x, x*rhs.y - y*rhs.x );
	}

	float Vector3::Normalize()
	{
		float length = Length();

		if ( length > 1e-06f )
		{
			float invlen = 1.0f / length;

			x *= invlen;
			y *= invlen;
			z *= invlen;
		}
		else
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;

			length = 0.0f;
		}

		return length;
	}

	float Vector3::Length() const
	{
		return Math::Sqrt( x * x + y * y + z * z );
	}

	float Vector3::SquareLength() const
	{
		return x * x + y * y + z * z;
	}

	bool Vector3::operator==( const Vector3& rhs )
	{
		return x == rhs.x &&
			   y == rhs.y &&
			   z == rhs.z;
	}

	bool Vector3::operator!=( const Vector3& rhs )
	{
		return !operator ==( rhs );
	}

	Vector3 Vector3::operator+( const Vector3& rhs )
	{
		return Vector3( x + rhs.x, y + rhs.y, z + rhs.z );
	}

	Vector3 Vector3::operator-( const Vector3& rhs )
	{
		return Vector3( x - rhs.x, y - rhs.y, z - rhs.z );
	}

	Vector3 Vector3::operator*( float scalar )
	{
		return Vector3( x * scalar, y * scalar, z * scalar );
	}

	float Vector3::operator*( const Vector3& rhs )
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vector3 Vector3::operator/( float scalar )
	{
		float inv = 1.0f / scalar;
		return Vector3( x * inv, y * inv, z * inv );
	}

	Vector3 Vector3::operator-()
	{
		return Vector3( -x, -y, -z );
	}

	Vector3& Vector3::operator+=( const Vector3& rhs )
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	Vector3& Vector3::operator-=( const Vector3& rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}

	Vector3& Vector3::operator*=( float scalar )
	{
		x *= scalar;
		x *= scalar;
		x *= scalar;

		return *this;
	}

	Vector3& Vector3::operator/=( float scalar )
	{
		float invscalar = 1.0f / scalar;
		x *= invscalar;
		x *= invscalar;
		x *= invscalar;

		return *this;
	}
}
