#include "Vge.h"

#ifdef VGE_D3D
	#include "VgeD3D.h"
#else
	#include "VgeOGL.h"
#endif

namespace Vge
{
	//
	// Graphics
	//
	Graphics::Graphics(Window* window)
		: mWindow(window)
//		, mLibLoader(null)
	{
		//mLibLoader = new LibLoader(VT("VgeD3D.dll"));
		////mLibLoader = new LibLoader(_VT("VgeOGL.dll"));
		//VFunction<Render*> func = mLibLoader->GetFunction(VT("Vge_CreateVGERenderer"));
		//if (func)
		//	mRenderer = func();
#ifdef VGE_D3D
		mRenderer = new D3DRenderer;
#else
		mRenderer = new OGLRenderer;
#endif

		if (!mRenderer->Create(mWindow))
			VGE_THROW(VT("[Graphics::Graphics] mRenderer->Create failed!\n"));

		mRenderer->SetAlphaBlend(false);
	}

	Graphics::~Graphics()
	{
		if (mRenderer)
		{
			//VFunctionVoid func = mLibLoader->GetFunction(VT("Vge_ReleaseVGERenderer"));
			//if (func)
			//	func(mRenderer);
			delete mRenderer;

			mRenderer = null;
		}

		//if (mLibLoader)
		//	delete mLibLoader;
	}

	void Graphics::Resize(Window* window)
	{
		mRenderer->Resize(window);
	}

	bool Graphics::BeginScene()
	{
		mRenderer->Clear(Color::Black);

		return mRenderer->BeginScene();
	}
	

	void Graphics::EndScene()
	{
		mRenderer->EndScene();
	}

	void Graphics::DrawSprite(Sprite* sprite)
	{
		mRenderer->DrawPrimitive(Render::PT_Triangle, 0, null, 0);
	}

	void Graphics::DrawText(Font* font, const String& text, int x, int y, const Color& color, dword align/* = ALIGN_Left*/)
	{
		mRenderer->DrawText(font, text, x, y, color, align);
	}

	Font* Graphics::CreateFont(const String& name, dword size, bool italic/* = false*/)
	{
		return mRenderer->CreateFont(name, size, italic);
	}

	void Graphics::ReleaseFont(Font* font)
	{
		mRenderer->ReleaseFont(font);
	}
}
