#include "Vge.h"

#include <windows.h>

namespace Vge
{
	LibLoader::LibLoader(const String& libname)
	{
		mHandle = (handle)::LoadLibrary(libname.Str());
		if (mHandle == null)
			VGE_THROW(VT("[LibLoader::LibLoader] ::LoadLibrary failed!\n"));
	}

	LibLoader::~LibLoader()
	{
		if (mHandle)
			::FreeLibrary((HMODULE)mHandle);
	}

	FuncObject LibLoader::GetFunction(const String& funcname)
	{
		if (mHandle == null)
			return null;

		return (FuncObject)::GetProcAddress((HMODULE)mHandle, ANSISTR(funcname).Str());
	}
}