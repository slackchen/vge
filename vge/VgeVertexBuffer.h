#pragma once

namespace Vge
{
	class VGE_API VertexBuffer : public RenderResource
	{
	public:
		VertexBuffer( dword size, bool isdynamic = false );
		~VertexBuffer();

	protected:
		void Resize( dword size );
	};
}