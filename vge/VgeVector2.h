#pragma once

namespace Vge
{
	class VGE_API Vector2
	{
	public:
		FORCEINLINE Vector2();

		FORCEINLINE Vector2(float _x, float _y);

		FORCEINLINE float SquareLength() const;

		FORCEINLINE float Length() const;

		FORCEINLINE float Normalize();

		FORCEINLINE Vector2 operator + ( float dis ) const;

		FORCEINLINE Vector2 operator + ( const Vector2& rhs ) const;

		FORCEINLINE Vector2& operator += ( float dis );

		FORCEINLINE Vector2 operator - ( float dis ) const;

		FORCEINLINE Vector2 operator - ( const Vector2& rhs ) const;

		FORCEINLINE Vector2& operator -= ( float dis );

		FORCEINLINE Vector2 operator * ( float n ) const;

		FORCEINLINE Vector2 operator * ( const Vector2& rhs ) const;

		FORCEINLINE Vector2& operator *= ( float n );

		FORCEINLINE Vector2 operator / ( float n ) const;

		FORCEINLINE Vector2& operator /= ( float n );

		float x,y;
	};
}