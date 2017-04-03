#pragma once

namespace Vge
{
	class Frame;

	class VGE_API Window
	{
	public:
		Window(Frame* frame);
		virtual ~Window();

		bool Create();

		void Destroy();

		void Update();

		virtual void Paint(Graphics* g);

		void SetWindowText(const String& text);

		void Show();

		void Hide();

		/**
		@param width The width of window.
		@param height The height of window.
		*/
		void SetSize(int width, int height);

		void SetSize(const Size& size);

		int GetWidth() const;

		int GetHeight() const;

		void SetClientSize(const Size& size);

		const Size& GetClientSize() const;

		void AdjustWindow();

		void ToggleFullScreen();

		void Resize(int width, int height);

		handle GetHandle() const;

		void SetUserData(dword userdata);

		dword GetUserData() const;

		Graphics* GetGraphics();

		void SetFullScreen(bool fullscreen) { mFullScreen = fullscreen; }

		bool GetFullScreen() const { return mFullScreen; }

		void SetVsync(bool vsync) { mVsync = vsync; }

		bool GetVsync() const { return mVsync; }

		void SetFocus(bool focus) { mFocus = focus; }

		inline bool GetFocus() const;

	protected:
		Frame* mFrame;
		handle mHandle;
		dword mUserData;
		Size mSize;
		Size mClientSize;
		Graphics* mGraphics;
		bool mFullScreen;
		bool mVsync;
		bool mFocus;

		Graphics* CreateGraphics();

		virtual void OnCreated(){}

		virtual void OnDestroy(){}
	};
}