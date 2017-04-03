/*
This file is part of Vge it is a Video Game Engine for game develop.
Copyright (C) 2008 N.G. of Libra++

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <Vge.h>

// Define exports macros
#ifdef VGEOGL_EXPORTS
#define VGEOGL_API __declspec(dllexport)
#else
#define VGEOGL_API/* __declspec(dllimport)*/
#endif

#include <gl/gl.h>
#pragma comment(lib, "Opengl32.lib")

namespace Vge
{
	class OGLRenderer : public Render
	{
	public:
		OGLRenderer();
		virtual ~OGLRenderer();

		virtual bool Create(Window* window);

		virtual void Release();

		virtual void Resize(Window* window);

		virtual void Clear(const Color& color);

		virtual bool BeginScene();

		virtual void EndScene();

		virtual void DrawPrimitive(PolygonType pt, dword count, void* data, dword stride);

		virtual void DrawText(Font* font, const String& text, int x, int y,
						const Color& color, dword align = ALIGN_Left);

		virtual void DrawSprite(Sprite* sprite);

		virtual void SetAlphaBlend(bool blend);

		virtual void SetEnableZBuffer(bool enable);

		virtual Font* CreateFont(const String& name, dword size, bool italic = false);

		virtual void ReleaseFont(Font*& font);

		virtual VertexDeclaration* CreateVertexDeclaration();

		virtual void ReleaseVertexDeclaration(VertexDeclaration*& vd);

		virtual VertexBuffer* CreateVertexBuffer();

		virtual void ReleaseVertexBuffer(VertexBuffer*& vb);

		virtual IndexBuffer* CreateIndexBuffer();

		virtual void ReleaseIndexBuffer(IndexBuffer*& ib);

	private:
		Window*	mWindow;
		PIXELFORMATDESCRIPTOR mPfd;
		DEVMODE	mDm;
		HGLRC	mGlrc;
		HDC		mHdc;

		void CheckChangeScreenMode();
		void CheckRestoreScreenMode();
	};
}

extern "C" VGEOGL_API Vge::Render* Vge_CreateVGERenderer();

extern "C" VGEOGL_API void Vge_ReleaseVGERenderer(Vge::Render* renderer);