#include "Vge.h"

namespace Vge
{
	const Matrix Matrix::IDENTITY = Matrix(Plane(1,0,0,0),Plane(0,1,0,0),Plane(0,0,1,0),Plane(0,0,0,1));

	Matrix::Matrix()
	{

	}

	Matrix::Matrix( const Matrix& rhs )
	{
		System::Memcpy((void*)m, rhs.m, sizeof(m));
	}


	Matrix::Matrix( const Plane& p1, const Plane& p2, const Plane& p3, const Plane& pw )
	{
		m[0][0] = p1.x; m[0][1] = p1.y;  m[0][2] = p1.z;  m[0][3] = p1.w;
		m[1][0] = p2.x; m[1][1] = p2.y;  m[1][2] = p2.z;  m[1][3] = p2.w;
		m[2][0] = p3.x; m[2][1] = p3.y;  m[2][2] = p3.z;  m[2][3] = p3.w;
		m[3][0] = pw.x; m[3][1] = pw.y;  m[3][2] = pw.z;  m[3][3] = pw.w;
	}

	Matrix::Matrix( const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& vw )
	{
		m[0][0] = v1.x; m[0][1] = v1.y;  m[0][2] = v1.z;  m[0][3] = 0.0f;
		m[1][0] = v2.x; m[1][1] = v2.y;  m[1][2] = v2.z;  m[1][3] = 0.0f;
		m[2][0] = v3.x; m[2][1] = v3.y;  m[2][2] = v3.z;  m[2][3] = 0.0f;
		m[3][0] = vw.x; m[3][1] = vw.y;  m[3][2] = vw.z;  m[3][3] = 1.0f;
	}

	void Matrix::Identity()
	{
		m[0][0] = 1; m[0][1] = 0;  m[0][2] = 0;  m[0][3] = 0;
		m[1][0] = 0; m[1][1] = 1;  m[1][2] = 0;  m[1][3] = 0;
		m[2][0] = 0; m[2][1] = 0;  m[2][2] = 1;  m[2][3] = 0;
		m[3][0] = 0; m[3][1] = 0;  m[3][2] = 0;  m[3][3] = 1;
	}

	Matrix Matrix::Transpose() const
	{
		Matrix mat;

		mat.m[0][0] = m[0][0];
		mat.m[0][1] = m[1][0];
		mat.m[0][2] = m[2][0];
		mat.m[0][3] = m[3][0];

		mat.m[1][0] = m[0][1];
		mat.m[1][1] = m[1][1];
		mat.m[1][2] = m[2][1];
		mat.m[1][3] = m[3][1];

		mat.m[2][0] = m[0][2];
		mat.m[2][1] = m[1][2];
		mat.m[2][2] = m[2][2];
		mat.m[2][3] = m[3][2];

		mat.m[3][0] = m[0][3];
		mat.m[3][1] = m[1][3];
		mat.m[3][2] = m[2][3];
		mat.m[3][3] = m[3][3];

		return mat;
	}

	float Matrix::Determinant() const
	{
		return	m[0][0] * (
			m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
			m[2][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) +
			m[3][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2])
			) -
			m[1][0] * (
			m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
			m[2][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
			m[3][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2])
			) +
			m[2][0] * (
			m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) -
			m[1][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
			m[3][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])
			) -
			m[3][0] * (
			m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) -
			m[1][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2]) +
			m[2][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])
			);
	}

	Matrix Matrix::Inverse() const
	{
		Matrix mat;
		const float	det = Determinant();

		if(det == 0.0f)
			return Matrix::IDENTITY;

		const float	invdet = 1.0f / det;

		mat.m[0][0] = invdet * (
			m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
			m[2][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) +
			m[3][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2])
			);
		mat.m[0][1] = -invdet * (
			m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
			m[2][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
			m[3][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2])
			);
		mat.m[0][2] = invdet * (
			m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) -
			m[1][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
			m[3][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])
			);
		mat.m[0][3] = -invdet * (
			m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) -
			m[1][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2]) +
			m[2][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])
			);

		mat.m[1][0] = -invdet * (
			m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
			m[2][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) +
			m[3][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2])
			);
		mat.m[1][1] = invdet * (
			m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
			m[2][0] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
			m[3][0] * (m[0][2] * m[2][3] - m[0][3] * m[2][2])
			);
		mat.m[1][2] = -invdet * (
			m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) -
			m[1][0] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
			m[3][0] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])
			);
		mat.m[1][3] = invdet * (
			m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) -
			m[1][0] * (m[0][2] * m[2][3] - m[0][3] * m[2][2]) +
			m[2][0] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])
			);

		mat.m[2][0] = invdet * (
			m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
			m[2][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) +
			m[3][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1])
			);
		mat.m[2][1] = -invdet * (
			m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
			m[2][0] * (m[0][1] * m[3][3] - m[0][3] * m[3][1]) +
			m[3][0] * (m[0][1] * m[2][3] - m[0][3] * m[2][1])
			);
		mat.m[2][2] = invdet * (
			m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) -
			m[1][0] * (m[0][1] * m[3][3] - m[0][3] * m[3][1]) +
			m[3][0] * (m[0][1] * m[1][3] - m[0][3] * m[1][1])
			);
		mat.m[2][3] = -invdet * (
			m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) -
			m[1][0] * (m[0][1] * m[2][3] - m[0][3] * m[2][1]) +
			m[2][0] * (m[0][1] * m[1][3] - m[0][3] * m[1][1])
			);

		mat.m[3][0] = -invdet * (
			m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
			m[2][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) +
			m[3][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
			);
		mat.m[3][1] = invdet * (
			m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
			m[2][0] * (m[0][1] * m[3][2] - m[0][2] * m[3][1]) +
			m[3][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1])
			);
		mat.m[3][2] = -invdet * (
			m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) -
			m[1][0] * (m[0][1] * m[3][2] - m[0][2] * m[3][1]) +
			m[3][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1])
			);
		mat.m[3][3] = invdet * (
			m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
			m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) +
			m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1])
			);

		return mat;
	}

}
