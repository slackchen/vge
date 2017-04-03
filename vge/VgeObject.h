#pragma once

namespace Vge
{
	//
	// Object
	//
	class VGE_API Object
	{
		VGE_DECLARE_BASE_CLASS(Object)

	public:
		Object()
		{
		}

		virtual ~Object()
		{
		}

		inline void* operator new(size_t size)
		{
			void* p = Vge::Memory::Allocate(size);
			System::Memset(p, 0, (uint)size);
			return p;
		}

		inline void* operator new(size_t size, void* p)
		{
			return p;
		}

		inline void* operator new[](size_t size)
		{
			void* p = Vge::Memory::Allocate(size);
			System::Memset(p, 0, (uint)size);
			return p;
		}

		inline void* operator new[](size_t size, void* p)
		{
			return p;
		}

		inline void operator delete(void * p)
		{
			return Vge::Memory::Deallocate(p);
		}

		inline void operator delete[](void * p)
		{
			return Vge::Memory::Deallocate(p);
		}

	protected:
	};

	class VGE_API ReferenceObject
	{
	public:
		ReferenceObject()
			: mRefCount(0)
		{
		}

		ReferenceObject* AddRef()
		{
			++mRefCount;
			return this;
		}

		void Release()
		{
			if (--mRefCount == 0)
				delete this;
		}

		void SetRefCount(int refcount) { mRefCount = refcount; }
		int GetRefCount() { return mRefCount; }

		static void RegisterReflection();

	private:
		int		mRefCount;
	};

	class VGE_API InteractiveObject
	{
	public:
		virtual ~InteractiveObject() = 0 {};

		virtual bool OnMouseEvent(Object* sender, MouseEvent& e) { return false; }
		virtual bool OnKeyDown(Object* sender, KeyboardEvent& e) { return false; }
		virtual bool OnKeyUp(Object* sender, KeyboardEvent& e) { return false; }
	};

	class VGE_API RenderableObject : public Object
	{
	public:

	};
}