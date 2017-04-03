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

#include "VgeOGL.h"

namespace Vge
{
	OGLRenderer::OGLRenderer()
		: mWindow(null)
		, mGlrc(null)
		, mHdc(null)
	{

	}

	OGLRenderer::~OGLRenderer()
	{
		Release();
	}

	bool OGLRenderer::Create(Window* window)
	{
		mWindow = window;

		CheckChangeScreenMode();

		memset(&mPfd, 0, sizeof(mPfd));
		mPfd.nSize        = sizeof(mPfd);
		mPfd.nVersion     = 1;
		mPfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		mPfd.iPixelType   = PFD_TYPE_RGBA;
		mPfd.cColorBits   = 32;
		mPfd.iLayerType	  = PFD_MAIN_PLANE;

		mHdc = ::GetDC((HWND)mWindow->GetHandle());
		int pf = ChoosePixelFormat(mHdc, &mPfd);
		if (pf == 0) {
			::MessageBox(NULL, VT("ChoosePixelFormat() failed:  ")
				VT("Cannot find a suitable pixel format."), VT("Error"), MB_OK); 
			return false;
		} 

		if (::SetPixelFormat(mHdc, pf, &mPfd) == FALSE) {
			::MessageBox(NULL, VT("SetPixelFormat() failed:  ")
				VT("Cannot set format specified."), VT("Error"), MB_OK);
			return false;
		} 

		DescribePixelFormat(mHdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &mPfd);

		mGlrc = ::wglCreateContext(mHdc);
		::wglMakeCurrent(mHdc, mGlrc);

		Size size = mWindow->GetClientSize();
		::glViewport(0, 0, size.width, size.height);

		return true;
	}

	void OGLRenderer::Release()
	{
		::wglMakeCurrent(mHdc, NULL);
		::ReleaseDC((HWND)mWindow->GetHandle(), mHdc);
		::wglDeleteContext(mGlrc);

		CheckRestoreScreenMode();
	}

	void OGLRenderer::CheckChangeScreenMode()
	{
		Size size = mWindow->GetClientSize();

		if (mWindow->GetFullScreen())
		{
			memset(&mDm, 0, sizeof(DEVMODE));
			mDm.dmSize=sizeof(DEVMODE);
			mDm.dmPelsWidth=size.width;
			mDm.dmPelsHeight=size.height;
			mDm.dmBitsPerPel=32;
			mDm.dmFields=DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
			::ChangeDisplaySettings(&mDm, CDS_FULLSCREEN);

			mWindow->AdjustWindow();
		}
		else
		{
			::ChangeDisplaySettings(NULL, 0);
		}
	}

	void OGLRenderer::CheckRestoreScreenMode()
	{
		::ChangeDisplaySettings(NULL, 0);
	}

	void OGLRenderer::Resize(Window* window)
	{
		CheckChangeScreenMode();

		Size size = mWindow->GetClientSize();
		::glViewport(0, 0, size.width, size.height);
	}

	void OGLRenderer::Clear(const Color& color)
	{
		::glClearColor(color.r,color.g,color.b, color.a);
		::glClear(GL_COLOR_BUFFER_BIT);
	}

	bool OGLRenderer::BeginScene()
	{
		// This is drawing test code!
		::glRotatef(1.0f, 0.0f, 0.0f, 1.0f);

		::glBegin(GL_TRIANGLES);
		::glColor3f(1.0f, 0.0f, 0.0f);
		::glVertex2i(0,  1);
		::glColor3f(0.0f, 1.0f, 0.0f);
		::glVertex2i(-1, -1);
		::glColor3f(0.0f, 0.0f, 1.0f);
		::glVertex2i(1, -1);
		::glEnd();

		return true;
	}

	void OGLRenderer::EndScene()
	{
		::glFlush();
		::SwapBuffers(mHdc);
	}

	void OGLRenderer::DrawPrimitive(PolygonType pt, dword count, void* data, dword stride)
	{

	}

	void OGLRenderer::DrawText(Font* font, const String& text, int x, int y,
								const Color& color, dword align/* = ALIGN_Left*/)
	{

	}

	void OGLRenderer::DrawSprite( Sprite* sprite )
	{

	}

	void OGLRenderer::SetAlphaBlend(bool blend)
	{

	}

	void OGLRenderer::SetEnableZBuffer(bool enable)
	{

	}

	Font* OGLRenderer::CreateFont(const String& name, dword size, bool italic/* = false*/)
	{
		return NULL;
	}

	void OGLRenderer::ReleaseFont(Font*& font)
	{

	}

	VertexDeclaration* OGLRenderer::CreateVertexDeclaration()
	{
		return NULL;
	}

	void OGLRenderer::ReleaseVertexDeclaration( VertexDeclaration*& vd )
	{

	}

	VertexBuffer* OGLRenderer::CreateVertexBuffer()
	{
		return NULL;
	}

	void OGLRenderer::ReleaseVertexBuffer( VertexBuffer*& vb )
	{

	}

	IndexBuffer* OGLRenderer::CreateIndexBuffer()
	{
		return NULL;
	}

	void OGLRenderer::ReleaseIndexBuffer( IndexBuffer*& ib )
	{

	}

}

extern "C" VGEOGL_API Vge::Render* Vge_CreateVGERenderer()
{
	return (Vge::Render*)new Vge::OGLRenderer;
};

extern "C" VGEOGL_API void Vge_ReleaseVGERenderer(Vge::Render* renderer)
{
	delete (Vge::OGLRenderer*)renderer;
};
