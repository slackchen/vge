#pragma once

// Define exports macros
#ifdef VGE_EXPORTS
#define VGE_API __declspec(dllexport)
#else
#define VGE_API/* __declspec(dllimport)*/
#pragma comment(lib, "Vge.lib")
#endif

// Disable some warning
#pragma warning (disable : 4251)
#pragma warning (disable : 4311)
#pragma warning (disable : 4312)

#pragma warning (disable : 4996)

#define VGE_PLATFORM_UNKNOWN	0
#define VGE_PLATFORM_WIN32		1

#ifdef _WIN32
#	define VGE_PLATFORM VGE_PLATFORM_WIN32
#else
#	define VGE_PLATFORM VGE_PLATFORM_UNKNOWN
#error Not supported this platform or compiler yet!
#endif

#if VGE_PLATFORM == VGE_PLATFORM_WIN32
#define VGE_D3D
#	if defined UNICODE
#		define VGE_UNICODE
#		define VT(str) L##str

#		define WIDEN(x) VT(x)
#		define __WFILE__ WIDEN(__FILE__)

#		define ANSISTR(x) StringUtil::UnicodeToAnsi(x)
#		define UNICODESTR(x) (x)
#	else
#		define VT(str) str

#		define ANSISTR(x) (x)
#		define UNICODESTR(x) StringUtil::AnsiToUnicode(x)
#	endif
#define MS_ALIGN(n) __declspec(align(n))
#define FORCEINLINE __forceinline
#endif

// STL headers
#include <cassert>
#include <iostream>
#include <sstream>
#include <memory>
#include <hash_map>
#include <typeinfo>
#include <cmath>

using namespace std;
using namespace stdext;

// Win32 headers
#ifdef _WIN32
#	include <tchar.h>
#	include <windows.h>
#endif

#ifdef _DEBUG
#	define VGE_ASSERT assert
#else
#	define VGE_ASSERT
#endif

// Type defines
namespace Vge
{
	typedef unsigned char byte;
	typedef unsigned short word;
	typedef unsigned long dword;
	typedef unsigned long ulong;
	typedef unsigned int uint;
	typedef wchar_t wchar;
	typedef void* handle;

	#ifdef VGE_UNICODE
		typedef wchar_t vchar;
	#else
		typedef char vchar;
	#endif

	#define null 0

	class Memory;
	class VgeException;
	class LibLoader;
	class System;
	class Console;

	class Name;
	class Size;
	class Color;
	class Sprite;
	class Font;
	class Graphics;
	class Render;

	class MessagePump;
	class Object;
	class MouseEvent;
	class KeyboardEvent;
	class Window;
	class Frame;
}

//#define VGE_MEMORY_MANAGEMENT

namespace Vge
{
	template< class T > inline T Align( const T Ptr, int alignment )
	{
		return (T)(((dword)Ptr + alignment - 1) & ~(alignment-1));
	}
}

// Include Vge headers

// System part of Vge
#include "VgeSystem.h"
#include "VgeMath.h"
#include "VgeMemory.h"
#include "VgeTemplate.h"
#include "VgeProperty.h"
#include "VgeRTTI.h"
#include "VgeObject.h"
#include "VgeThread.h"
#include "VgeVector2.h"
#include "VgeVector3.h"
#include "VgePlane.h"
#include "VgeMatrix.h"
#include "VgeString.h"
#include "VgeName.h"
#include "VgeStream.h"
#include "VgeException.h"
#include "VgeLibLoader.h"
#include "VgeConsole.h"

// Graphics part of Vge
#include "VgeSize.h"
#include "VgeColor.h"
#include "VgeRenderResource.h"
#include "VgeTexture.h"
#include "VgeVertexDeclaration.h"
#include "VgeVertexBuffer.h"
#include "VgeIndexBuffer.h"
#include "VgeSprite.h"
#include "VgeRender.h"
#include "VgeGraphics.h"

// Frame part of Vge
#include "VgeEvent.h"
#include "VgeMessagePump.h"
#include "VgeWindow.h"
#include "VgeFrame.h"

#include "VgeComponent.h"

extern "C" bool Vge_Init();
extern "C" void Vge_Uninit();

