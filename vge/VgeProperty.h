#pragma once

namespace Vge
{
	template <class T>
	class PropertyBase
	{
	public:
		inline PropertyBase() {}
		inline PropertyBase(const T& value)
			: mProperty(value) {}

	protected:
		T mProperty;
	};

	template <class T>
	class ReadOnlyProperty : public PropertyBase<T>
	{
	public:
		inline operator T() const
		{
			return mProperty;
		}

		inline T& operator ()()
		{
			return mProperty;
		}

	private:
	};

	template <class T>
	class WriteOnlyProperty : public PropertyBase<T>
	{
	public:
		inline T& operator = (const T& value)
		{
			mProperty = value;
			return mProperty;
		}
	};

	template <class T>
	class Property : public PropertyBase<T>
	{
	public:
		inline operator T() const
		{
			return mProperty;
		}

		inline T& operator = (const T& value)
		{
			mProperty = value;
			return mProperty;
		}
		
		inline T& operator ()()
		{
			return mProperty;
		}
	};

#define VGE_PROPERTY(type, name, func) \
protected: type name;\
public: virtual void Set##func(type v);\
public: virtual type Get##func();

#define VGE_PROPERTY_READONLY(type, name, func) \
protected: type name;\
public: virtual type Get##func();

#define VGE_SYNTHESIZE(type, name, func) \
protected: type name;\
public: virtual void Set##func(type v) { name = v; }\
public: virtual type Get##func() { return name; }
	
#define VGE_SYNTHESIZE_REF(type, name, func) \
protected: type name;\
public: virtual void Set##func(const type& v) { name = v; }\
public: virtual const type& Get##func() { return name; }

#define VGE_SYNTHESIZE_READONLY(type, name, func) \
protected: type name;\
public: virtual type Get##func() { return name; }

#define VGE_SYNTHESIZE_READONLY_REF(type, name, func) \
protected: type name;\
public: virtual const type& Get##func() { return name; }
}