#pragma once

namespace Vge
{
	class VGE_API Matrix
	{
	public:
		MS_ALIGN(16) float m[4][4];
		MS_ALIGN(16) static const Matrix IDENTITY;

		FORCEINLINE Matrix();

		FORCEINLINE Matrix( const Matrix& rhs );

		FORCEINLINE Matrix( const Plane& p1, const Plane& p2, const Plane& p3, const Plane& pw );

		FORCEINLINE Matrix( const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& vw );

		FORCEINLINE void Identity();

		FORCEINLINE Matrix Transpose() const;

		FORCEINLINE float Determinant() const;

		FORCEINLINE Matrix Inverse() const;

		FORCEINLINE Matrix operator * ( const Matrix& rhs );
	};
}