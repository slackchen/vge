#pragma once

namespace Vge
{
	//enum { MAX_CLASS_NAME = 32 };

	////
	//// PropertyType
	////
	//enum VgePropertyType
	//{
	//	VPT_Unknown,
	//	VPT_Bool,
	//	VPT_Dword,
	//	VPT_Int,
	//	VPT_Float,
	//	VPT_String,
	//	VPT_Enum,
	//	VPT_Ptr,
	//	VPT_MAX
	//};

	//template <class T>
	//class PropertyType
	//{
	//public:
	//	static VgePropertyType sTypeID;
	//};

	//typedef long Enum;
	//typedef void* Ptr;

	//template<class T> VgePropertyType PropertyType<T>::sTypeID = VPT_Unknown;
	//template<> VgePropertyType PropertyType<bool>::sTypeID = VPT_Bool;
	//template<> VgePropertyType PropertyType<dword>::sTypeID = VPT_Dword;
	//template<> VgePropertyType PropertyType<int>::sTypeID = VPT_Int;
	//template<> VgePropertyType PropertyType<float>::sTypeID = VPT_Float;
	//template<> VgePropertyType PropertyType<String>::sTypeID = VPT_String;
	//template<> VgePropertyType PropertyType<Enum>::sTypeID = VPT_Enum;
	//template<> VgePropertyType PropertyType<Ptr>::sTypeID = VPT_Ptr;

	////
	//// AbstractProperty
	////
	//class VGE_API AbstractProperty
	//{
	//public:
	//	virtual VgePropertyType GetType() const = 0;

	//protected:
	//	const char* mName;
	//};

	////
	//// TypedProperty
	////
	//template <class T>
	//class TypedProperty : public AbstractProperty
	//{
	//public:
	//	virtual VgePropertyType GetType() const
	//	{
	//		return mPropertyType.sTypeID;
	//	}

	//protected:
	//	PropertyType<T> mPropertyType;
	//};

	//template <class OwnerType, class T>
	//class Property : public TypedProperty<T>
	//{
	//public:
	//	typedef T (OwnerType::*GetterType)();
	//	typedef void (OwnerType::*SetterType)(T value);

	//	Property(const char* name, GetterType getter, SetterType setter)
	//		: mName(name), mGetter(getter), mSetter(setter)
	//	{
	//	}

	//	const char* GetName() const { return mName; }

	//	T GetValue(Object* object)
	//	{
	//		return object->*mGetter();
	//	}

	//	void SetValue(Object* object, T value)
	//	{
	//		if (mSetter == null)
	//		{
	//			VGE_ASSERT(false);
	//			return;
	//		}

	//		object->*mSetter(value);
	//	}

	//protected:
	//	GetterType mGetter;
	//	SetterType mSetter;
	//	const char* mName;
	//};

	//template <class OwnerType>
	//class RTTIPropertyManager
	//{
	//public:
	//	bool RegisterProperty(const Property<OwnerType, bool>& property)
	//	{
	//		mBoolPropertyMap.insert( BoolPropertyMap::value_type(property.GetName(), property));

	//		return true;
	//	}

	//	bool RegisterProperty(const Property<OwnerType, dword>& property)
	//	{
	//		mDwordPropertyMap.insert( BoolPropertyMap::value_type(property.GetName(), property));

	//		return true;
	//	}

	//	bool RegisterProperty(const Property<OwnerType, int>& property)
	//	{
	//		mIntPropertyMap.insert( IntPropertyMap::value_type(property.GetName(), property));

	//		return true;
	//	}

	//	bool RegisterProperty(const Property<OwnerType, float>& property)
	//	{
	//		mFloatPropertyMap.insert( FloatPropertyMap::value_type(property.GetName(), property));

	//		return true;
	//	}

	//	bool RegisterProperty(const Property<OwnerType, String>& property)
	//	{
	//		mStringPropertyMap.insert( StringPropertyMap::value_type(property.GetName(), property));

	//		return true;
	//	}

	//	bool RegisterProperty(const Property<OwnerType, string>& property)
	//	{
	//		mUnknownPropertyMap.insert( UnknownPropertyMap::value_type(property.GetName(), property));

	//		return true;
	//	}

	//protected:
	//	typedef map<string, Property<OwnerType, bool> > BoolPropertyMap;
	//	typedef map<string, Property<OwnerType, dword> > DwordPropertyMap;
	//	typedef map<string, Property<OwnerType, int> > IntPropertyMap;
	//	typedef map<string, Property<OwnerType, float> > FloatPropertyMap;
	//	typedef map<string, Property<OwnerType, String> > StringPropertyMap;
	//	typedef map<string, Property<OwnerType, string> > UnknownPropertyMap;

	//	BoolPropertyMap mBoolPropertyMap;
	//	DwordPropertyMap mDwordPropertyMap;
	//	IntPropertyMap mIntPropertyMap;
	//	FloatPropertyMap mFloatPropertyMap;
	//	StringPropertyMap mStringPropertyMap;
	//	UnknownPropertyMap mUnknownPropertyMap;
	//};

	//typedef dword ClassID;
	//typedef Object* (*ClassFactoryFunc)(ClassID classid);
	//typedef void (*RegisterReflectionFunc)();

	////
	//// RTTI
	////
	//class RTTI
	//{
	//public:

	//	RTTI(ClassID classid, const char* classname, RTTI* basertti,
	//			ClassFactoryFunc classfactory, RegisterReflectionFunc regreflection)
	//		: mClassID(classid), mBaseRTTI(basertti), mCreateFactory(classfactory),
	//			mRegisterReflection(regreflection)
	//	{
	//		strcpy(mClassName, classname);
	//	}

	//	RTTI* GetBaseRTTI() const
	//	{
	//		return mBaseRTTI;
	//	}

	//private:
	//	ClassID	mClassID;
	//	char mClassName[MAX_CLASS_NAME];
	//	RTTI* mBaseRTTI;
	//	ClassFactoryFunc mCreateFactory;
	//	RegisterReflectionFunc mRegisterReflection;
	//};

	////
	//// RTTIRootWrapper
	////
	//template <class T, ClassID CLID>
	//class RTTIRootWrapper
	//{
	//public:
	//	const static ClassID sClassID = CLID;

	//	RTTIRootWrapper();

	//	static T* Create();
	//	static void RegisterReflection();
	//	static inline RTTI* GetClassRTTI() { return &sRTTI; }
	//	virtual RTTI* GetRTTI() { return &sRTTI; }

	//	template<class PT>
	//	static bool RegisterProperty(const char* name, typename Property<T, PT>::GetterType getter,
	//		typename Property<T, PT>::SetterType setter)
	//	{
	//		return sRTTIPropertyManager.RegisterProperty(Property<T, PT>(name, getter, setter));
	//	}

	//protected:
	//	static RTTI sRTTI;
	//	static RTTIPropertyManager<T> sRTTIPropertyManager;
	//};

	//template <class T, ClassID CLID>
	//RTTIPropertyManager<T> RTTIRootWrapper<T, CLID>::sRTTIPropertyManager;

	//template<class T, ClassID CLID>
	//RTTI RTTIRootWrapper<T, CLID>::sRTTI(CLID, typeid(T).name(), null, (ClassFactoryFunc)T::Create,
	//										(RegisterReflectionFunc)T::RegisterReflection);

	//template<class T, ClassID CLID>
	//RTTIRootWrapper<T, CLID>::RTTIRootWrapper()
	//{
	//}

	//template<class T, ClassID CLID>
	//T* RTTIRootWrapper<T, CLID>::Create()
	//{
	//	return new T();
	//}

	//template<class T, ClassID CLID>
	//void RTTIRootWrapper<T, CLID>::RegisterReflection()
	//{
	//}

	////
	//// RTTIWrapper
	////
	//template <class T, class BaseClass, ClassID CLID>
	//class RTTIWrapper : public BaseClass
	//{
	//public:
	//	const static ClassID sClassID = CLID;

	//	RTTIWrapper();

	//	static T* Create();
	//	static void RegisterReflection();
	//	static inline RTTI* GetClassRTTI() { return &sRTTI; }
	//	virtual RTTI* GetRTTI() { return &sRTTI; }

	//	template<class PT>
	//	static bool RegisterProperty(const char* name, typename Property<T, PT>::GetterType getter,
	//									typename Property<T, PT>::SetterType setter)
	//	{
	//		return sRTTIPropertyManager.RegisterProperty(Property<T, PT>(name, getter, setter));
	//	}

	//protected:
	//	static RTTI sRTTI;
	//	static RTTIPropertyManager<T> sRTTIPropertyManager;
	//};

	//template <class T, class BaseClass, ClassID CLID>
	//RTTIPropertyManager<T> RTTIWrapper<T, BaseClass, CLID>::sRTTIPropertyManager;

	//template<class T, class BaseClass, ClassID CLID>
	//RTTI RTTIWrapper<T, BaseClass, CLID>::sRTTI(CLID, typeid(T).name(), BaseClass::GetClassRTTI(),
	//		(ClassFactoryFunc)T::Create, (RegisterReflectionFunc)T::RegisterReflection);

	//template<class T, class BaseClass, ClassID CLID>
	//RTTIWrapper<T, BaseClass, CLID>::RTTIWrapper()
	//{
	//}

	//template<class T, class BaseClass, ClassID CLID>
	//T* RTTIWrapper<T, BaseClass, CLID>::Create()
	//{
	//	return new T();
	//}

	//template<class T, class BaseClass, ClassID CLID>
	//void RTTIWrapper<T, BaseClass, CLID>::RegisterReflection()
	//{
	//}

	//template<class DestT>
	//DestT VCast(Object* object)
	//{
	//	RTTI* drt = DestT::GetRTTI();
	//	if (drt == null)
	//		return null;

	//	RTTI* rt = object->GetRTTI();
	//	while (rt)
	//	{
	//		if (drt == rt)
	//			return (DestT)object;

	//		rt = rt->GetBaseRTTI();
	//	}

	//	return null;
	//}


#define VGE_DECLARE_BASE_CLASS(class) \
	public: \
		Property<int> RefCount; \
	private:

#define VGE_DELEGATE_FUNC_PARAM Func func, VGE_DELEGATE_PARAM_DEFINE
#define VGE_DELEGATE_FUNC_PARAM_CALL func, VGE_DELEGATE_PARAM
#define VGE_DELEGATE_SUFIX(N) Delegate##N
#define VGE_MULTICALL_SUFIX(N) MultiCall##N
#define VGE_DELEGATE_FUNC_PARAM_TYPEF_SUFIX(N) ,typename P##N

template <typename T, typename Func>
class Delegate 
{
public:
	Delegate(T* obj, Func func)
		: mObject(obj)
		, mFunc(func)
	{
	}

	Delegate()
		: mObject(null)
		, mFunc(null)
	{

	}

public:
	T* mObject;
	Func mFunc;
};

// void
#define VGE_DELEGATE Delegate
#define VGE_MULTICALL MultiCall

#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func
#define VGE_DELEGATE_PARAM_DEFINE
#define VGE_DELEGATE_PARAM

#include "VgeDelegate.h"

// 1 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate1
#define VGE_MULTICALL MultiCall1
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1
#define VGE_DELEGATE_PARAM_DEFINE P1 p1
#define VGE_DELEGATE_PARAM p1

#include "VgeDelegate.h"

// 2 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate2
#define VGE_MULTICALL MultiCall2
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2
#define VGE_DELEGATE_PARAM p1, p2

#include "VgeDelegate.h"

// 3 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate3
#define VGE_MULTICALL MultiCall3
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3
#define VGE_DELEGATE_PARAM p1, p2, p3

#include "VgeDelegate.h"

// 4 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate4
#define VGE_MULTICALL MultiCall4
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4
#define VGE_DELEGATE_PARAM p1, p2, p3, p4

#include "VgeDelegate.h"

// 5 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate5
#define VGE_MULTICALL MultiCall5
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5

#include "VgeDelegate.h"

// 6 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate6
#define VGE_MULTICALL MultiCall6
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5, P6
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5, p6

#include "VgeDelegate.h"

// 7 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate7
#define VGE_MULTICALL MultiCall7
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5, P6, P7
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5, p6, p7

#include "VgeDelegate.h"

// 8 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate8
#define VGE_MULTICALL MultiCall8
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5, P6, P7, P8
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5, p6, p7, p8

#include "VgeDelegate.h"

// 9 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate9
#define VGE_MULTICALL MultiCall9
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5, P6, P7, P8, P9
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5, p6, p7, p8, p9

#include "VgeDelegate.h"

// 10 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate10
#define VGE_MULTICALL MultiCall10
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5, p6, p7, p8, p9, p10

#include "VgeDelegate.h"

// 11 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate11
#define VGE_MULTICALL MultiCall11
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11

#include "VgeDelegate.h"

// 12 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate12
#define VGE_MULTICALL MultiCall12
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12

#include "VgeDelegate.h"

// 13 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate13
#define VGE_MULTICALL MultiCall13
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13

#include "VgeDelegate.h"

// 14 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate14
#define VGE_MULTICALL MultiCall14
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14

#include "VgeDelegate.h"

// 15 param
#undef VGE_DELEGATE 
#undef VGE_MULTICALL
#undef VGE_DELEGATE_FUNC_PARAM_TYPEF
#undef VGE_DELEGATE_FUNC_PARAM_TYPE
#undef VGE_DELEGATE_PARAM_DEFINE
#undef VGE_DELEGATE_PARAM

#define VGE_DELEGATE Delegate15
#define VGE_MULTICALL MultiCall15
#define VGE_DELEGATE_FUNC_PARAM_TYPEF typename Func, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15
#define VGE_DELEGATE_FUNC_PARAM_TYPE Func, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15
#define VGE_DELEGATE_PARAM_DEFINE P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15
#define VGE_DELEGATE_PARAM p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15

#include "VgeDelegate.h"

template <typename T, typename Func>
Delegate<T, Func> NewDelegate(T* obj, Func func)
{
	return Delegate<T, Func>(obj, func);
}

template <typename T, typename Func>
Delegate<T, Func> NewDelegate(const SharedPtr<T>& obj, Func func)
{
	return Delegate<T, Func>(obj, func);
}

}