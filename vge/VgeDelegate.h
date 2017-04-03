

//template <typename T, typename Func>
//class VGE_DELEGATE 
//{
//public:
//	VGE_DELEGATE(T* obj, Func func)
//		: mObject(obj)
//		, mFunc(func)
//	{
//	}
//
//	VGE_DELEGATE()
//		: mObject(null)
//		, mFunc(null)
//	{
//
//	}
//
//public:
//	T* mObject;
//	Func mFunc;
//};

template <typename T, VGE_DELEGATE_FUNC_PARAM_TYPEF>
class VGE_MULTICALL
{
public:
	typedef Delegate<T, Func> DelegateType;
	typedef Func FuncType;

	void operator += (const DelegateType& delegate)
	{
		mDelegates.Add(delegate);
	}

	void operator -= (const DelegateType& delegate)
	{
		mDelegates.Remove(delegate);
	}

	void operator()(VGE_DELEGATE_PARAM_DEFINE)
	{
		List<DelegateType>::Iterator itBegin = mDelegates.First();
		List<DelegateType>::Iterator itEnd = mDelegates.Last();

		for (List<DelegateType>::Iterator it = itBegin; it != itEnd; ++it)
			(it->mObject->*it->mFunc)(VGE_DELEGATE_PARAM);
	}

	List<DelegateType> mDelegates;
};


//template <typename T, typename Func>
//VGE_DELEGATE<T, Func> NewDelegate(T* obj, Func func)
//{
//	return VGE_DELEGATE<T, Func>(obj, func);
//}
