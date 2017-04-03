#pragma once

namespace Vge
{
	typedef void* FuncObject;

	template<class VRet>
	class VFunction
	{
	public:
		VFunction(FuncObject func)
			: mFunc(func)
		{
		}

		VRet operator()()
		{
			typedef VRet (*Func)();
			return ((Func)mFunc)();
		}

		template <class T1>
		VRet operator()(T1 p1)
		{
			typedef VRet (*Func)(T1);
			return ((Func)mFunc)(p1);
		}

		template <class T1, class T2>
		VRet operator()(T1 p1, T2 p2)
		{
			typedef VRet (*Func)(T1, T2);
			return ((Func)mFunc)(p1, p2);
		}

		template <class T1, class T2, class T3>
		VRet operator()(T1 p1, T2 p2, T3 p3)
		{
			typedef VRet (*Func)(T1, T2, T3);
			return ((Func)mFunc)(p1, p2, p3);
		}

		template <class T1, class T2, class T3, class T4>
		VRet operator()(T1 p1, T2 p2, T3 p3, T4 p4)
		{
			typedef VRet (*Func)(T1, T2, T3, T4);
			return ((Func)mFunc)(p1, p2, p3, p4);
		}

		template <class T1, class T2, class T3, class T4, class T5>
		VRet operator()(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
		{
			typedef VRet (*Func)(T1, T2, T3, T4, T5);
			return ((Func)mFunc)(p1, p2, p3, p4, p5);
		}

		template <class T1, class T2, class T3, class T4, class T5, class T6>
		VRet operator()(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
		{
			typedef VRet (*Func)(T1, T2, T3, T4, T5, T6);
			return ((Func)mFunc)(p1, p2, p3, p4, p5, p6);
		}

		template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		VRet operator()(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
		{
			typedef VRet (*Func)(T1, T2, T3, T4, T5, T6, T7);
			return ((Func)mFunc)(p1, p2, p3, p4, p5, p6, p7);
		}

		operator bool() const
		{
			return mFunc != null;
		}

	private:
		void* mFunc;
	};

	class VFunctionVoid
	{
	public:
		VFunctionVoid(FuncObject func)
			: mFunc(func)
		{
		}

		void operator()()
		{
			typedef void (*Func)();
			((Func)mFunc)();
		}

		template <class T1>
		void operator()(T1 p1)
		{
			typedef void (*Func)(T1);
			((Func)mFunc)(p1);
		}

		template <class T1, class T2>
		void operator()(T1 p1, T2 p2)
		{
			typedef void (*Func)(T1, T2);
			((Func)mFunc)(p1, p2);
		}

		template <class T1, class T2, class T3>
		void operator()(T1 p1, T2 p2, T3 p3)
		{
			typedef void (*Func)(T1, T2, T3);
			((Func)mFunc)(p1, p2, p3);
		}

		template <class T1, class T2, class T3, class T4>
		void operator()(T1 p1, T2 p2, T3 p3, T4 p4)
		{
			typedef void (*Func)(T1, T2, T3, T4);
			((Func)mFunc)(p1, p2, p3, p4);
		}

		template <class T1, class T2, class T3, class T4, class T5>
		void operator()(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
		{
			typedef void (*Func)(T1, T2, T3, T4, T5);
			((Func)mFunc)(p1, p2, p3, p4, p5);
		}

		template <class T1, class T2, class T3, class T4, class T5, class T6>
		void operator()(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
		{
			typedef void (*Func)(T1, T2, T3, T4, T5, T6);
			((Func)mFunc)(p1, p2, p3, p4, p5, p6);
		}

		template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		void operator()(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
		{
			typedef void (*Func)(T1, T2, T3, T4, T5, T6, T7);
			((Func)mFunc)(p1, p2, p3, p4, p5, p6, p7);
		}

		operator bool() const
		{
			return mFunc != null;
		}

	private:
		void* mFunc;
	};

	class VGE_API LibLoader
	{
	public:
		LibLoader(const String& libname);
		~LibLoader();

		FuncObject GetFunction(const String& funcname);

	private:
		handle mHandle;
	};
}