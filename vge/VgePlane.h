#pragma once

namespace Vge
{
	class Plane : public Vector3
	{
	public:
		float	w;

		Plane( float _x, float _y, float _z, float _w );
	};
}