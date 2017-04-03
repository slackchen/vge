#include "Vge.h"

namespace Vge
{
	Frame::Frame()
		: mWindow(null)
	{
	}

	Frame::~Frame()
	{
		if (mWindow)
			delete mWindow;
	}

	bool Frame::Run(Window* window)
	{
		mWindow = window;

		return Run() == 0;
	}

	int Frame::Run()
	{
		Timer::Init();

		if (!mWindow->Create())
			return 1;

		while (true)
		{
			if (!MessagePump::DoEvent())
			{
				mWindow->Destroy();
				break;
			}

			mWindow->Update();
		}

		return 0;
	}
}

