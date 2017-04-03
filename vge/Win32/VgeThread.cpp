#include "Vge.h"

namespace Vge
{
	struct ThreadInfo : Object
	{
		Thread* pThread;
		Runable* pRunable;
	};

	int Vge_ThreadStartRoutine( void* param )
	{
		int ret = 0;

		ThreadInfo* info = (ThreadInfo*)param;
		if ( info->pRunable )
			ret = info->pRunable->Run();

		delete info;

		return ret;
	}

	Thread::Thread( Runable* pRunable, bool suspend )
	{
		assert( pRunable );

		ThreadInfo* info = new ThreadInfo;
		info->pThread = this;
		info->pRunable = pRunable;

		mId = 0;
		mHandle = ::CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Vge_ThreadStartRoutine, info, NULL, &mId );
		if ( suspend )
			Suspend();
	}

	Thread::~Thread()
	{
		::CloseHandle( mHandle );
	}

	void Thread::Suspend()
	{
		::SuspendThread( mHandle );
	}

	void Thread::Resume()
	{
		::ResumeThread( mHandle );
	}

	void Thread::Terminate()
	{
		::TerminateThread( mHandle, 0 );
	}

	void Thread::Wait( dword millisecond )
	{
		::WaitForSingleObject( mHandle, millisecond );
	}

	void Thread::Sleep( dword millisecond )
	{
		::Sleep( millisecond );
	}

	ThreadLocker::ThreadLocker()
	{
		BOOL ret = ::InitializeCriticalSectionAndSpinCount(&mLock, 1000);
		assert(ret);
	}

	ThreadLocker::~ThreadLocker()
	{
		::DeleteCriticalSection(&mLock);
	}

	void ThreadLocker::Lock()
	{
		::EnterCriticalSection(&mLock);
	}

	void ThreadLocker::Unlock()
	{
		::LeaveCriticalSection(&mLock);
	}


	ThreadAutoLocker::ThreadAutoLocker(ThreadLocker& locker)
		: mLocker(locker)
	{
		mLocker.Lock();
	}

	ThreadAutoLocker::~ThreadAutoLocker()
	{
		mLocker.Unlock();
	}

}
