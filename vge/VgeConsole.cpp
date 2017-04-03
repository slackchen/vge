#include "Vge.h"

namespace Vge
{
	void Console::Print(const String& str)
	{
//#ifdef VGE_UNICODE
		static bool first = true;
		if (first)
		{
			wcout.imbue(locale("chs"));
			first = false;
		}
//#endif
		Cout << str.Str();
		Cout.flush();
	}

	void Console::PrintLine(const String& str)
	{
		Print(str + VT("\n"));
	}
}