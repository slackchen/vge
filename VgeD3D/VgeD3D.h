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
#ifdef VGED3D_EXPORTS
#define VGED3D_API __declspec(dllexport)
#else
#define VGED3D_API/* __declspec(dllimport)*/
#endif

#include <d3d9.h>
#include <d3dx9.h>
#	pragma comment(lib, "d3d9.lib")
#ifdef _DEBUG
#	pragma comment(lib, "d3dx9d.lib")
#else
#	pragma comment(lib, "d3dx9.lib")
#endif

namespace Vge
{
	//
	// D3DFont
	//
	class D3DFont : public Font
	{
	public:
		D3DFont(ID3DXFont* font);
		~D3DFont();

		virtual Size GetTextWidth(const String& text);

		inline ID3DXFont* GetD3DXFont() const { return mD3DXFont; }

	private:
		ID3DXFont*	mD3DXFont;
	};

	//
	// D3DRenderer
	//
	class Sprite;

	class D3DRenderer : public Render
	{
	public:
		D3DRenderer();
		virtual ~D3DRenderer();

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

		LPDIRECT3DDEVICE9 GetDevice() const { return mDevice; }

	private:
		bool OnLostDevice();
		bool OnResetDevice();

		LPDIRECT3D9				mD3D;
		LPDIRECT3DDEVICE9		mDevice;
		D3DPRESENT_PARAMETERS	mD3Dpp;

		typedef List<ID3DXFont*> FontList;
		FontList				mFontList;

		Window*					mWindow;
	};
}

extern "C" VGED3D_API Vge::Render* Vge_CreateRenderer();

extern "C" VGED3D_API void Vge_ReleaseRenderer(Vge::Render* renderer);

