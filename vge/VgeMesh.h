#pragma once

namespace Vge
{
	class VGE_API SubMesh
	{
	public:
	};

	typedef vector<SubMesh*> SubMeshList;

	class VGE_API Mesh
	{
	public:

	protected:
		SubMeshList		m_SubMeshes;
	};
}