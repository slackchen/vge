#pragma once

namespace Vge
{
	class VGE_API Vector3
	{
	public:
		static const Vector3 ZERO;
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;
		static const Vector3 UNIT_ALL;

		FORCEINLINE Vector3();

		FORCEINLINE Vector3( float _x, float _y, float _z );

		FORCEINLINE Vector3( const Vector3& rhs );

		FORCEINLINE Vector3 Cross( const Vector3& rhs ) const;

		FORCEINLINE float Normalize();

		FORCEINLINE float Length() const;

		FORCEINLINE float SquareLength() const;

		FORCEINLINE bool operator == ( const Vector3& rhs );

		FORCEINLINE bool operator != ( const Vector3& rhs );

		FORCEINLINE Vector3 operator + ( const Vector3& rhs );

		FORCEINLINE Vector3 operator - ( const Vector3& rhs );

		FORCEINLINE Vector3 operator * ( float scalar );

		FORCEINLINE float operator * ( const Vector3& rhs );

		FORCEINLINE Vector3 operator / ( float scalar );

		FORCEINLINE Vector3 operator -();

		FORCEINLINE Vector3& operator += ( const Vector3& rhs );

		FORCEINLINE Vector3& operator -= ( const Vector3& rhs );

		FORCEINLINE Vector3& operator *= ( float scalar );

		FORCEINLINE Vector3& operator /= ( float scalar );

		float x, y, z;
	};
}
