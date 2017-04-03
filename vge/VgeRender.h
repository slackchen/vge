#pragma once

namespace Vge
{
	enum
	{
		ALIGN_Left		= 0x00000001,
		ALIGN_Center	= 0x00000002,
		ALIGN_Right		= 0x00000004,
		ALIGN_Top		= 0x00000008,
		ALIGN_VCenter	= 0x00000010,
		ALIGN_Bottom	= 0x00000020
	};

	class VGE_API Render
	{
	public:
		enum PolygonType
		{
			PT_Triangle,
		};

		virtual bool Create(Window* window) = 0;

		virtual void Release() = 0;

		virtual void Resize(Window* window) = 0;

		virtual void Clear(const Color& color) = 0;

		virtual bool BeginScene() = 0;

		virtual void EndScene() = 0;

		virtual void DrawPrimitive(PolygonType pt, dword count, void* data, dword stride) = 0;

		virtual void DrawText(Font* font, const String& text, int x, int y,
							const Color& color, dword align = ALIGN_Left) = 0;

		virtual void DrawSprite(Sprite* sprite) = 0;

		virtual void SetAlphaBlend(bool blend) = 0;

		virtual void SetEnableZBuffer(bool enable) = 0;

		virtual Font* CreateFont(const String& name, dword size, bool italic = false) = 0;

		virtual void ReleaseFont(Font*& font) = 0;

		virtual VertexDeclaration* CreateVertexDeclaration() = 0;

		virtual void ReleaseVertexDeclaration(VertexDeclaration*& vd) = 0;

		virtual VertexBuffer* CreateVertexBuffer() = 0;

		virtual void ReleaseVertexBuffer(VertexBuffer*& vb) = 0;

		virtual IndexBuffer* CreateIndexBuffer() = 0;

		virtual void ReleaseIndexBuffer(IndexBuffer*& ib) = 0;
	};

	extern Render* gRender;
}