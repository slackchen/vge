#pragma once

namespace Vge
{
	template <typename T>
	class SharedPtr
	{
	public:
		SharedPtr()
			: mObjPtr(null)
		{

		}

		SharedPtr(T* p)
			: mObjPtr(p)
		{
			if (mObjPtr)
				mObjPtr->RefCount()++;
		}

		SharedPtr(const SharedPtr& rhs)
			: mObjPtr(rhs.mObjPtr)
		{
			if (mObjPtr)
				mObjPtr->RefCount()++;
		}

		~SharedPtr()
		{
			if (mObjPtr && --mObjPtr->RefCount() == 0)
			{
				{
					delete mObjPtr;
					mObjPtr = null;
				}
			}
		}

		SharedPtr& operator = (T* p)
		{
			if (p)
				p->RefCount()++;

			if (mObjPtr)
				mObjPtr->RefCount()--;

			mObjPtr = p;

			return *this;
		}

		SharedPtr& operator = (const SharedPtr& rhs)
		{
			if (this == &rhs)
				return *this;

			if (rhs.mObjPtr)
				rhs.mObjPtr->RefCount()++;

			if (mObjPtr)
				mObjPtr->RefCount()--;

			mObjPtr = rhs.mObjPtr;

			return *this;
		}

		T* operator->() const
		{
			assert(mObjPtr);
			return mObjPtr;
		}

		T& operator*() const
		{
			assert(mObjPtr);
			return *mObjPtr;
		}

		operator T&() const
		{
			assert(mObjPtr);
			return *mObjPtr;
		}

		operator T*() const
		{
			assert(mObjPtr);
			return mObjPtr;
		}

		operator int() const
		{
			return (int)mObjPtr;
		}

	private:
		T* mObjPtr;
	};

	class VGE_API FPSCounter
	{
	public:
		FPSCounter();

		void Update();
		dword GetFPS() const;

	private:
		dword mLastTime;
		dword mCounter;
		dword mFPS;
	};

	class VGE_API Timer
	{
	public:
		static void Init();

		static dword GetRealTime();
	};

	class VGE_API System
	{
	public:
		static void Sleep(dword milliseconds);

		static dword GetTickCount();

		static void* Memcpy(void* dest, const void* src, uint size);

		static void* Memset(void* dest, byte data, uint size);

		static dword StrLen(const vchar* str);

		static vchar* StrCpy(vchar* str1, const vchar* str2);

		static vchar* StrCat(vchar* str1, const vchar* str2);

		static dword Stricmp(const vchar* str1, const vchar* str2);
	};
}

#define YIELD_BEGIN { static int _y_times = 0; int _y_state=0; if (_y_times == _y_state++) {
#define YIELD _y_times++; return; } else if (_y_times == _y_state++) { 
#define YIELD_RET(x) _y_times++; return x; } else if (_y_times == _y_state++) { 
#define YIELD_END } else {}  _y_times = 0; }