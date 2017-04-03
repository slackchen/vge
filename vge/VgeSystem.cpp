#include "Vge.h"

namespace Vge
{
	//
	// FPSCounter
	//
	FPSCounter::FPSCounter()
		: mCounter(0), mFPS(0)
	{
		mLastTime = System::GetTickCount();
	}

	void FPSCounter::Update()
	{
		if (System::GetTickCount() - mLastTime >= 1000)
		{
			mLastTime = System::GetTickCount();
			mFPS = mCounter;
			mCounter = 0;
		}
		++mCounter;
	}

	dword FPSCounter::GetFPS() const
	{
		return mFPS;
	}

	//
	// System
	//
	void System::Sleep(dword milliseconds)
	{
		::Sleep(milliseconds);
	}

	dword System::GetTickCount()
	{
		return Timer::GetRealTime();
	}

	void* System::Memcpy(void* dest,const void* src, uint size)
	{
		return ::memcpy(dest, src, size);
	}

	void* System::Memset(void* dest, byte data, uint size)
	{
		return ::memset(dest, data, size);
	}


	dword System::StrLen(const vchar* str)
	{
		return (dword)_tcslen(str);
	}

	vchar* System::StrCpy(vchar* str1, const vchar* str2)
	{
		return _tcscpy(str1, str2);
	}

	vchar* System::StrCat(vchar* str1, const vchar* str2)
	{
		return _tcscat(str1, str2);
	}

	dword System::Stricmp(const vchar* str1, const vchar* str2)
	{
		return _tcsicmp(str1, str2);
	}

	//
	// Timer
	//
	LARGE_INTEGER HighPerformanceFreq;
	BOOL HighPerformanceTimerSupport = FALSE;

	void Timer::Init()
	{
		// disable hires timer on multiple core systems, bios bugs result in bad hires timers.
		SYSTEM_INFO sysinfo;
		DWORD affinity, sysaffinity;
		GetSystemInfo(&sysinfo);
		dword affinityCount = 0;

		// count the processors that can be used by this process
		if (GetProcessAffinityMask( GetCurrentProcess(), &affinity, &sysaffinity ))
		{
			for (dword i=0; i<32; ++i)
			{
				if ((1<<i) & affinity)
					affinityCount++;
			}
		}

		if (sysinfo.dwNumberOfProcessors == 1 || affinityCount == 1)
		{
			HighPerformanceTimerSupport = QueryPerformanceFrequency(&HighPerformanceFreq);
		}
		else
		{
			HighPerformanceTimerSupport = FALSE;
		}
	}

	dword Timer::GetRealTime()
	{
		if (HighPerformanceTimerSupport)
		{
			LARGE_INTEGER nTime;
			QueryPerformanceCounter(&nTime);
			return dword((nTime.QuadPart) * 1000 / HighPerformanceFreq.QuadPart);
		}
		return GetTickCount();
	}
}