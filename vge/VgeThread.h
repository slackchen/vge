#pragma once

namespace Vge
{
	class VGE_API Runable
	{
	public:
		virtual int Run() = 0;
	};

	class VGE_API Thread
	{
	public:
		Thread( Runable* pRunable, bool suspend = false );
		~Thread();

		void Suspend();

		void Resume();

		void Terminate();

		void Wait( dword millisecond = 0xFFFFFFFF );

		static void Sleep( dword millisecond );

	protected:
		dword	mId;
		handle	mHandle;

	};

	class VGE_API ThreadLocker
	{
	public:
		ThreadLocker();
		~ThreadLocker();

		void Lock();
		void Unlock();

	private:
#if VGE_PLATFORM == VGE_PLATFORM_WIN32
		CRITICAL_SECTION mLock;
#endif
	};

	class VGE_API ThreadAutoLocker
	{
	public:
		ThreadAutoLocker(ThreadLocker& locker);
		~ThreadAutoLocker();

	private:
		ThreadLocker& mLocker;
	};
}