#include "Vge.h"

#include <windows.h>

namespace Vge
{
	Window::Window(Frame* frame)
		: mFrame(frame)
		, mHandle(null)
		, mGraphics(null)
		, mFullScreen(false)
		, mVsync(false)
		, mFocus(true)
	{
	}

	Window::~Window()
	{
		Destroy();
	}

	bool Window::Create()
	{
		extern LRESULT CALLBACK VgeWinProc(HWND, UINT, WPARAM, LPARAM);

		const String strClass = VT("Vge_Window");

		WNDCLASSEX wcex = {0};
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_DBLCLKS;
		wcex.lpszClassName = strClass.Str();
		wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wcex.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
		wcex.hIconSm = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;
		wcex.hInstance = GetModuleHandle(NULL);
		wcex.lpfnWndProc = (WNDPROC)VgeWinProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;

		if (!::RegisterClassEx(&wcex))
			VGE_THROW(VT("[Window::Window] RegisterClassEx failed!\n"));

		DWORD dwStyle = WS_POPUP;
		if (!mFullScreen)
			dwStyle |= WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;

		dwStyle |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

		DWORD dwStyleEx = !mFullScreen ? WS_EX_APPWINDOW | WS_EX_WINDOWEDGE : WS_EX_APPWINDOW;//WS_EX_TOPMOST;
		RECT rcWindow = { CW_USEDEFAULT, 0, mClientSize.width, mClientSize.height};

		mSize = mClientSize;

		mHandle = (handle)::CreateWindowEx(dwStyleEx, strClass.Str(), VT("VGE Window"), dwStyle,
			rcWindow.left, rcWindow.top, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top,
			::GetDesktopWindow(), NULL, ::GetModuleHandle(NULL), NULL);

		if (mHandle == null)
			VGE_THROW(VT("[Window::Window] CreateWindowEx failed!\n"));

		SetUserData((dword)this);

		mGraphics = CreateGraphics();

		OnCreated();

		AdjustWindow();

		Show();

		::SetForegroundWindow((HWND)mHandle);

		return true;
	}

	void Window::Destroy()
	{
		if (mHandle)
		{
			OnDestroy();

			if (mGraphics)
			{
				delete mGraphics;
				mGraphics = null;
			}

			mHandle = null;
		}
	}

	void Window::Update()
	{
		Graphics* g = GetGraphics();

		if (!g->BeginScene())
			return;

		Paint(g);

		g->EndScene();

		if (!GetFocus())
			System::Sleep(1);
	}

	void Window::Paint(Graphics* g)
	{
	}

	void Window::SetWindowText(const String& text)
	{
		::SetWindowText((HWND)mHandle, text.Str());
	}

	void Window::Show()
	{
		::ShowWindow((HWND)mHandle, SW_SHOW);
	}

	VOID Window::Hide()
	{
		::ShowWindow((HWND)mHandle, SW_HIDE);
	}

	void Window::SetSize(int width, int height)
	{
		SetSize(Size(width, height));
	}

	void Window::SetSize(const Size& size)
	{
		mSize = size;
	}

	int Window::GetWidth() const
	{
		return mSize.width;
	}

	int Window::GetHeight() const
	{
		return mSize.height;
	}

	void Window::SetClientSize(const Size& size)
	{
		mClientSize = size;

		if (mHandle)
			AdjustWindow();
	}

	const Size& Window::GetClientSize() const
	{
		return mClientSize;
	}

	void Window::AdjustWindow()
	{
		DWORD dwStyle = WS_POPUP;
		if (!mFullScreen)
			dwStyle |= WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
		dwStyle |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

		DWORD dwStyleEx = !mFullScreen ? WS_EX_APPWINDOW | WS_EX_WINDOWEDGE : WS_EX_APPWINDOW;//WS_EX_TOPMOST;

		mSize.width = mClientSize.width + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
		mSize.height = mClientSize.height + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

		RECT rcWindow;
		rcWindow.left = (GetSystemMetrics(SM_CXSCREEN) - mSize.width) / 2;
		rcWindow.top = (GetSystemMetrics(SM_CYSCREEN) - mSize.height - GetSystemMetrics(SM_CYCAPTION)) / 2;

		rcWindow.right = rcWindow.left + mSize.width;
		rcWindow.bottom = rcWindow.top + mSize.height;

		::SetWindowLong((HWND)mHandle, GWL_STYLE, dwStyle);
		::SetWindowLong((HWND)mHandle, GWL_EXSTYLE, dwStyleEx);

		::SetWindowPos((HWND)mHandle, !mFullScreen ? HWND_NOTOPMOST : HWND_TOPMOST, rcWindow.left, rcWindow.top,
			rcWindow.right - rcWindow.left,  rcWindow.bottom - rcWindow.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	}

	void Window::ToggleFullScreen()
	{
		SetFullScreen(!GetFullScreen());
		Resize(mClientSize.width, mClientSize.height);
	}

	void Window::Resize(int width, int height)
	{
		mClientSize.width = width;
		mClientSize.height = height;

		if (GetFullScreen())
			AdjustWindow();

		mGraphics->Resize(this);

		if (!GetFullScreen())
			AdjustWindow();
	}

	handle Window::GetHandle() const
	{
		return mHandle;
	}

	void Window::SetUserData(dword userdata)
	{
		mUserData = userdata;
		::SetWindowLong((HWND)mHandle, GWL_USERDATA, (LONG)userdata);
	}

	dword Window::GetUserData() const
	{
		return mUserData;
	}

	Graphics* Window::GetGraphics()
	{
		if (mGraphics == null)
		{
			return CreateGraphics();
		}

		return mGraphics;
	}

	bool Window::GetFocus() const
	{
		return mFocus && !::IsIconic((HWND)mHandle);
	}

	Graphics* Window::CreateGraphics()
	{
		if (mGraphics)
			delete mGraphics;

		mGraphics = new Graphics(this);
		return mGraphics;
	}
}

LRESULT CALLBACK VgeWinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Vge::Window* window = reinterpret_cast<Vge::Window*>(::GetWindowLong(hWnd, GWL_USERDATA));
	if (window)
	{
		switch (uMsg)
		{
		case WM_ACTIVATEAPP:
			{
				window->SetFocus(wParam != 0);
			}
			break;
		case WM_KEYDOWN:
			{
				if (wParam == VK_ESCAPE)
					PostQuitMessage(0);

				if (wParam == VK_F6)
				{
					Vge::Size clientsize = window->GetClientSize();
					if (clientsize.width == 800 && clientsize.height == 600)
						window->Resize(1024, 768);
					else
						window->Resize(800, 600);
				}
				
			}
			break;
		case WM_SYSKEYDOWN:
			{
				if (wParam == VK_RETURN)
					window->ToggleFullScreen();
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}