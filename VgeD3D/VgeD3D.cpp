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

#include "VgeD3D.h"

namespace Vge
{
	//
	// Matrix
	//
	Matrix Matrix::operator*( const Matrix& rhs )
	{
		Matrix mat;
		D3DXMatrixMultiply( (D3DXMATRIX*)mat.m, (D3DXMATRIX*)m, (D3DXMATRIX*)rhs.m );
		return mat;
	}

	//
	// D3DFont
	//
	D3DFont::D3DFont(ID3DXFont* font)
		: mD3DXFont(font)
	{
	}

	D3DFont::~D3DFont()
	{
		if (mD3DXFont)
		{
			mD3DXFont->Release();
			mD3DXFont = NULL;
		}
	}

	Size D3DFont::GetTextWidth(const String& text)
	{
		HDC dc = mD3DXFont->GetDC();

		SIZE size;
		::GetTextExtentPoint(dc, text.Str(), (int)text.Length(), &size);

		return Size(size.cx, size.cy);
	}

	//
	// D3DRenderer
	//

	Render* gRender = NULL;

	D3DRenderer::D3DRenderer()
		: mD3D(NULL)
		, mDevice(NULL)
	{
		gRender = this;
	}

	D3DRenderer::~D3DRenderer()
	{
		Release();
	}

	bool D3DRenderer::Create(Window* window)
	{
		Size clientsize = window->GetClientSize();
		mWindow = window;

		if( NULL == (mD3D = Direct3DCreate9(D3D_SDK_VERSION)))
			return false;

		D3DDISPLAYMODE d3ddm; 
		if(D3D_OK!=mD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)) 
			return false; 

		ZeroMemory( &mD3Dpp, sizeof(mD3Dpp) );
		mD3Dpp.SwapEffect = !window->GetFullScreen() ? D3DSWAPEFFECT_COPY : D3DSWAPEFFECT_FLIP;
		mD3Dpp.Windowed   = !window->GetFullScreen();
		mD3Dpp.BackBufferWidth = clientsize.width;
		mD3Dpp.BackBufferHeight = clientsize.height;
		mD3Dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		mD3Dpp.EnableAutoDepthStencil = TRUE;
		mD3Dpp.AutoDepthStencilFormat = D3DFMT_D16;
		mD3Dpp.PresentationInterval = window->GetVsync() ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

		if( FAILED( mD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, (HWND)window->GetHandle(),
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&mD3Dpp, &mDevice ) ) )
		{

			if( FAILED( mD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, (HWND)window->GetHandle(),
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&mD3Dpp, &mDevice ) ) )
				return false;
		}

		return true;
	}

	void D3DRenderer::Release()
	{
		if (mDevice)
		{
			mDevice->Release();
			mDevice = NULL;
		}

		if (mD3D)
		{
			mD3D->Release();
			mD3D = NULL;
		}
	}

	void D3DRenderer::Resize(Window* window)
	{
		mWindow = window;

		OnLostDevice();
		OnResetDevice();
	}


	void D3DRenderer::Clear(const Color& color)
	{
		mDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0 );
	}

	bool D3DRenderer::BeginScene()
	{
		HRESULT hr = mDevice->TestCooperativeLevel();
		if (hr == D3DERR_DEVICELOST)
		{
			OnLostDevice();

			return false;
		}
		else if (hr == D3DERR_DEVICENOTRESET)
		{
			if(!OnResetDevice())
				return false; 
		}

		mDevice->BeginScene();

		return true;
	}

	void D3DRenderer::EndScene()
	{
		mDevice->EndScene();
		mDevice->Present(NULL, NULL, NULL, NULL);
	}

	void D3DRenderer::DrawPrimitive(PolygonType pt, dword count, void* data, dword stride)
	{
		switch (pt)
		{
		case PT_Triangle:
			{
				mDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, count, data, stride);
				break;
			}
		}
	}

	void D3DRenderer::DrawText(Font* font, const String& text, int x, int y,
							const Color& color, dword align/* = ALIGN_Left*/)
	{
		RECT rc = {x, y, 0, 0};
		DWORD dwFormat = DT_NOCLIP;

		if ((align & ALIGN_Right) ||
			(align & ALIGN_Bottom) ||
			(align & ALIGN_Center) ||
			(align & ALIGN_VCenter))
		{
			Size size = font->GetTextWidth(text);

			if (align & ALIGN_Right)
				rc.left = x - size.width;
			else if (align & ALIGN_Center)
				rc.left = x - size.width / 2;

			if (align & ALIGN_Bottom)
				rc.top = y - size.height;
			else if (align & ALIGN_VCenter)
				rc.top = y - size.height / 2;
		}

#ifndef VGE_UNICODE
		WString wtext = StringUtil::AnsiToUnicode(text);
		static_cast<D3DFont*>(font)->GetD3DXFont()->DrawTextW(NULL, wtext.Str(), -1, &rc, dwFormat, color);
#else
		static_cast<D3DFont*>(font)->GetD3DXFont()->DrawText(NULL, text.c_str(), -1, &rc, dwFormat, color);
#endif
	}

	void D3DRenderer::DrawSprite( Sprite* sprite )
	{

	}

	void D3DRenderer::SetAlphaBlend(bool blend)
	{
		mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, blend);
	}

	void D3DRenderer::SetEnableZBuffer(bool enable)
	{
		mDevice->SetRenderState(D3DRS_ZENABLE, (BOOL)enable);
	}

	Font* D3DRenderer::CreateFont(const String& name, dword size, bool italic/* = false*/)
	{
		Font* font = NULL;

		D3DXFONT_DESC d3dfd;
		ZeroMemory(&d3dfd, sizeof(d3dfd));

		StringUtil::CopyString(d3dfd.FaceName, name.Str());

		d3dfd.Height = size;
		d3dfd.Italic = italic;

		//d3dfd.Weight = 400;
		//d3dfd.OutputPrecision = 3;
		//d3dfd.PitchAndFamily = 50;
		//d3dfd.Quality = 1;

		ID3DXFont* d3dfont = NULL;
		if (FAILED(D3DXCreateFontIndirect(mDevice, &d3dfd, &d3dfont)))
			return NULL;

		font = new D3DFont(d3dfont);
		if (font == NULL)
		{
			d3dfont->Release();
			return NULL;
		}

		mFontList.Add(d3dfont);

		return font;
	}

	void D3DRenderer::ReleaseFont(Font*& font)
	{
		mFontList.Remove(static_cast<D3DFont*>(font)->GetD3DXFont());

		delete (D3DFont*)font;
		font = NULL;
	}

	bool D3DRenderer::OnLostDevice()
	{
		FontList::Iterator it = mFontList.First();
		while (it != mFontList.Last())
		{
			ID3DXFont* font = *it;
			if (FAILED(font->OnLostDevice()))
				return false;

			it++;
		}

		return true;
	}

	bool D3DRenderer::OnResetDevice()
	{
		// Release device resource
		// ...

		// Reset device
		Size clientsize = mWindow->GetClientSize();

		mD3Dpp.hDeviceWindow = (HWND)mWindow->GetHandle();
		mD3Dpp.Windowed   = !mWindow->GetFullScreen();
		mD3Dpp.BackBufferWidth = clientsize.width;
		mD3Dpp.BackBufferHeight = clientsize.height;
		//mD3Dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		//mD3Dpp.AutoDepthStencilFormat = D3DFMT_D16;
		mD3Dpp.PresentationInterval = mWindow->GetVsync() ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

		if (FAILED(mDevice->Reset(&mD3Dpp)))
			return false;

		// Reload device resource
		FontList::Iterator it = mFontList.First();
		while (it != mFontList.Last())
		{
			ID3DXFont* font = *it;
			if (FAILED(font->OnResetDevice()))
				return false;

			it++;
		}

		return true;
	}

	VertexDeclaration* D3DRenderer::CreateVertexDeclaration()
	{
		return NULL;
	}

	void D3DRenderer::ReleaseVertexDeclaration( VertexDeclaration*& vd )
	{

	}

	VertexBuffer* D3DRenderer::CreateVertexBuffer()
	{
		return NULL;
	}

	void D3DRenderer::ReleaseVertexBuffer(VertexBuffer*& vb)
	{

	}

	IndexBuffer*D3DRenderer:: CreateIndexBuffer()
	{
		return NULL;
	}

	void D3DRenderer::ReleaseIndexBuffer(IndexBuffer*& ib)
	{

	}
}

extern "C" VGED3D_API Vge::Render* Vge_CreateRenderer()
{
	return (Vge::Render*)new Vge::D3DRenderer;
};

extern "C" VGED3D_API void Vge_ReleaseRenderer(Vge::Render* renderer)
{
	delete (Vge::D3DRenderer*)renderer;
};
