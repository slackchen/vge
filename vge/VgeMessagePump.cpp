#include "Vge.h"

#include <windows.h>

namespace Vge
{
	bool MessagePump::DoEvent()
	{
		MSG msg;
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return false;

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);

			return true;
		}

		return true;
	}
}