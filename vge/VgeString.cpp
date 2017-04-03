#include "Vge.h"

namespace Vge
{
	//
	// StringUtil
	//
	String StringUtil::ToString(int n)
	{
		StrStream str;
		str << n;
		return str.str().c_str();
		//String str;
		//str.Format(VT("%d"), n);
		//return str;
	}

	String StringUtil::ToString(dword n)
	{
		StrStream str;
		str << n;
		return str.str().c_str();
		//String str;
		//str.Format(VT("%u"), n);
		//return str;
	}

	String StringUtil::ToString(float f)
	{
		StrStream str;
		str << f;
		return str.str().c_str();
		//String str;
		//str.Format(VT("%f"), f);
		//return str;
	}

	String StringUtil::ToString(double d)
	{
		StrStream str;
		str << (float)d;
		return str.str().c_str();
		//String str;
		//str.Format(VT("%f"), (float)d);
		//return str;
	}

	wchar* StringUtil::AnsiToUnicode(char* str, dword slen, wchar* wstr, dword wlen)
	{
		::MultiByteToWideChar(CP_ACP, 0, str, slen+1, wstr, wlen);
		return wstr;
	}

	char* StringUtil::UnicodeToAnsi(wchar* wstr, dword wlen, char* str, dword slen)
	{
		::WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, slen, null, null);
		return str;
	}

	WString StringUtil::AnsiToUnicode(const AString& astr)
	{
		int len = ::MultiByteToWideChar(CP_ACP, 0, astr.Str(), -1, null, 0);
		if (len == -1)
			return WString();

		WString wstr;
		wstr.Resize(len);
		::MultiByteToWideChar(CP_ACP, 0, astr.Str(), -1, &wstr[0], len);

		return wstr;
	}

	AString StringUtil::UnicodeToAnsi(const WString& wstr)
	{
		int len = ::WideCharToMultiByte(CP_ACP, 0, wstr.Str(), -1, null, 0, null, null);
		if (len == -1)
			return AString();

		AString astr;
		astr.Resize(len);
		::WideCharToMultiByte(CP_ACP, 0, wstr.Str(), -1, &astr[0], len, null, null);

		return astr;
	}

	void StringUtil::CopyString(vchar* str1, const vchar* str2, size_t count /* = 0x7FFFFFFF */)
	{
		size_t len = _tcslen(str2);
		if (count > len)
			count = len;

		_tcsncpy(str1, str2, count);
		str1[count] = 0;
	}
	
	bool StringUtil::CompareWildcard(const String& str1, const vchar* comaprestr)
	{
		vchar* dstr = (vchar*)str1.Str();
		vchar* cstr = (vchar*)comaprestr;

		while (*dstr != 0 && *cstr != 0)
		{
			if( *cstr == VT('*'))
			{
				while (*cstr == VT('*')) cstr++;

				if (*cstr != 0 && *cstr == VT('?'))
					cstr++;

				while (*dstr != 0 && *cstr != *dstr)
					dstr++;
			}
			else if (*cstr == VT('?'))
			{
				dstr++; cstr++;
			}
			else
			{
				if (*cstr != *dstr)
					return false;

				dstr++; cstr++;
			}
		}

		if (*cstr == 0 && *dstr == 0)
			return true;

		return false;
	}
}
