#pragma once

namespace Vge
{
	//
	// Font
	//
	class VGE_API Font
	{
	public:
		virtual Size GetTextWidth(const String& text) = 0;
	};

	//
	// Graphics
	//
	class VGE_API Graphics
	{
	public:
		Graphics(Window* window);
		~Graphics();

		void Resize(Window* window);

		bool BeginScene();

		void EndScene();

		void DrawSprite(Sprite* sprite);

		void DrawText(Font* font, const String& text, int x, int y, const Color& color, dword align = ALIGN_Left);

		Font* CreateFont(const String& name, dword size, bool italic = false);

		void ReleaseFont(Font* font);

	private:
		Window*		mWindow;
//		LibLoader*	mLibLoader;
		Render*	mRenderer;
	};
}
