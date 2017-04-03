#include "Vge.h"

namespace Vge
{
	Plane::Plane( float _x, float _y, float _z, float _w )
		: Vector3( _x, _y, _z )
		, w( _w )
	{

	}
}