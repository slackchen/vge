#pragma once

namespace Vge
{
	template <class T>
	class StringBuffer : public Array<T>
	{
	public:
		typedef T ValueType;

		StringBuffer()
		{
			Resize(1);
			(*this)[0] = 0;
		}

		StringBuffer(const T* str)
		{
			Assign(str);
		}

		StringBuffer(const Name& name)
		{
			Assign(name.GetString());
		}

		StringBuffer& operator=(const T* str)
		{
			return Assign(str);
		}

		StringBuffer& operator=(const StringBuffer& rhs)
		{
			return Assign(rhs);
		}

		StringBuffer& operator=(const Name& name)
		{
			return Assign(name.GetString());
		}

		StringBuffer& Assign(const T* str)
		{
			assert(str);

			dword size = System::StrLen(str) + 1;
			Resize(size);
			System::Memcpy(GetData(), str, size * sizeof(T));
			return *this;
		}

		StringBuffer& Assign(const StringBuffer& str)
		{
			dword size = str.Length() + 1;
			Resize(size);
			System::Memcpy(GetData(), str.GetData(), size * sizeof(T));
			return *this;
		}

		dword Length() const
		{
			return Array<T>::Length() - 1;
		}

		T* Str() const
		{
			return (T*)GetData();
		}

		void Format(const T* str, ...)
		{
			va_list args;
			va_start(args, str);
#ifdef VGE_UNICODE
			int len = _vscwprintf( str, args ) // _vscprintf doesn't count
				+ 1; // terminating '\0'

			vswprintf(Str(), str, args);
#else
			int len = _vscprintf( str, args ) // _vscprintf doesn't count
				+ 1; // terminating '\0'

			Resize(len);

			vsprintf(Str(), str, args);
#endif;

			va_end(args);


		}
	};

	typedef StringBuffer<char> AString;
	typedef StringBuffer<wchar_t> WString;

#ifdef VGE_UNICODE
	typedef WString String;
	typedef wstringstream StrStream;

#define  Cout wcout
#else
	typedef AString String;
	typedef stringstream StrStream;

#define  Cout cout
#endif

	class VGE_API StringUtil
	{
	public:
		static String ToString(int n);
		static String ToString(dword n);
		static String ToString(float f);
		static String ToString(double d);

		static wchar* AnsiToUnicode(char* str, dword slen, wchar* wstr, dword wlen);
		static char* UnicodeToAnsi(wchar* wstr, dword wlen, char* str, dword slen);

		static WString AnsiToUnicode(const AString& astr);
		static AString UnicodeToAnsi(const WString& wstr);

		static void CopyString(vchar* str1, const vchar* str2, size_t count = 0x7FFFFFFF);

		static bool CompareWildcard(const String& str1, const vchar* comaprestr);
	};
}

inline Vge::String operator+(const Vge::String& str1, const Vge::String& str2)
{
	Vge::dword sizeOfChar = sizeof(Vge::String::ValueType);
	Vge::String str;
	str.Resize(str1.Length() + str2.Length() + 1);
	Vge::System::Memcpy(str.GetData(), str1.GetData(), str1.Length() * sizeOfChar);
	Vge::System::Memcpy(str.GetData() + str1.Length() * sizeOfChar, str2.GetData(), (str2.Length() + 1) * sizeOfChar);
	return str;
}


inline VGE_API Vge::String operator + (const Vge::vchar* str1, const Vge::String& str2)
{
	return Vge::String(str1) + str2;
}

inline VGE_API Vge::String operator + (const Vge::String& str, int n)
{
	return str + Vge::StringUtil::ToString(n);
}

inline VGE_API Vge::String operator + (const Vge::String& str, Vge::dword n)
{
	return str + Vge::StringUtil::ToString(n);
}

inline VGE_API Vge::String operator + (int n, const Vge::String& str)
{
	return  Vge::StringUtil::ToString(n) + str;
}

inline VGE_API Vge::String operator + (const Vge::String& str, float f)
{
	return str + Vge::StringUtil::ToString(f);
}

inline VGE_API Vge::String operator + (float f, const Vge::String& str)
{
	return  Vge::StringUtil::ToString(f) + str;
}

inline VGE_API Vge::String operator + (const Vge::String& str, double d)
{
	return str + Vge::StringUtil::ToString(d);
}

inline VGE_API Vge::String operator + (double d, const Vge::String& str)
{
	return  Vge::StringUtil::ToString(d) + str;
}
