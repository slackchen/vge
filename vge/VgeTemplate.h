#pragma once

namespace Vge
{
	// --------------------------------------
	// Array Declaration
	// --------------------------------------
	template <class T, class Key = T>
	class Array
	{
	public:
		Array(dword setBlockSize = 1)
			: mElements(null)
			, mAlloced(0)
			, mNumOfElement(0)
			, mBlockSize(setBlockSize)
		{
		}

		Array(T* data, dword numOfElement, dword setBlockSize = 1)
			: mNumOfElement(numOfElement)
			, mBlockSize(setBlockSize)
		{
			Resize(numOfElement);

			for (dword i = 0; i < numOfElement; ++i)
				mElements[i] = data[i];
		}

		~Array()
		{
			delete[] mElements;
		}

		Array(const Array& other)
			: mElements(null)
			, mAlloced(0)
			, mNumOfElement(0)
			, mBlockSize(1)
		{
			operator=(other);
		}

		Array& operator = (const Array& rhs)
		{
			if (this == &rhs)
				return *this;

			Resize(rhs.mNumOfElement);

			for (dword i = 0; i < rhs.mNumOfElement; ++i)
				mElements[i] = rhs[i];

			return *this;
		}

		const T& operator [] (dword index) const
		{
			VGE_ASSERT(index < mAlloced);

			return mElements[index];
		}

		T& operator [] (dword index)
		{
			VGE_ASSERT(index >= 0 && index < mAlloced);

			return mElements[index];
		}

		T* GetElement(dword index) const
		{
			if (index >= mNumOfElement)
				return null;

			return &mElements[index];
		}

		T* GetData() const
		{
			return mElements;
		}

		dword Length() const
		{
			return mNumOfElement;
		}

		void Add(const T& element)
		{
			dword oldsize = mNumOfElement;

			if (oldsize + 1 > mAlloced)
				Resize(oldsize + 1);

			mElements[oldsize++] = element;
			mNumOfElement = oldsize;
		}

		void RemoveAt(dword index)
		{
			VGE_ASSERT(index < mNumOfElement);
			if (index >= mNumOfElement)
				return;

			for (dword i = index; i < mNumOfElement - 1; ++i)
				mElements[i] = mElements[i + 1];

			--mNumOfElement;
		}

		void Remove(const T& value)
		{
			dword index = 0;
			while (index < mNumOfElement)
			{
				if (mElements[index] != value)
					index++;
				else
					break;
			}


			if (index >= mNumOfElement)
				return;

			for (dword i = index; i < mNumOfElement - 1; ++i)
				mElements[i] = mElements[i + 1];

			--mNumOfElement;
		}

		void Clear()
		{
			delete[] mElements;

			mElements = null;
			mNumOfElement = 0;
		}

		void Resize(dword setNum)
		{
			mAlloced = Align(setNum, mBlockSize);

			T* data = new T[mAlloced];

			for (dword i = 0; i < min(mNumOfElement, mAlloced); ++i)
				data[i] = mElements[i];

			delete[] mElements;

			mElements = data;
			mNumOfElement = setNum;
		}

		dword GetBytes() const
		{
			return mNumOfElement * sizeof(T);
		}

		class Iterator;

		Iterator First()
		{
			return Iterator(mNumOfElement == 0 ?
								mElements :
								&mElements[0]);
		}

		Iterator Last()
		{
			return Iterator(mNumOfElement == 0 ?
								mElements :
								&mElements[mNumOfElement]);
		}

		class Iterator
		{
		public:
			Iterator() : mData(null) {}

			Iterator(T* data)
			{
				mData = data;
			}

			Iterator(const Iterator& it)
			{
				mData = it.mData;
			}

			Iterator& operator=(const Iterator& it)
			{
				mData = it.mData;
				return *this;
			}

			Iterator operator++()
			{
				++mData;
				return Iterator(mData);
			}

			Iterator operator++(int dummy)
			{
				T* data = mData;
				++mData;
				return Iterator(data);
			}

			bool operator == (const Iterator& it)
			{
				return mData == it.mData;
			}

			bool operator != (const Iterator& it)
			{
				return !operator==(it);
			}

			T& operator*()
			{
				return (T&)(*mData);
			}

			T* operator->()
			{
				return (T*)&(*mData);
			}

		private:
			T*	mData;
		};


	private:
		T* mElements;
		dword mAlloced;
		dword mNumOfElement;
		dword mBlockSize;
	};

	// --------------------------------------
	// List Declaration
	// --------------------------------------
	template <class T, class Key = T>
	class List
	{
	public:
		struct Node
		{
			T		mData;
			Node*	mNext;
		};

		List()
			: mHead(null)
			, mTail(null)
		{
		}

		~List()
		{
			Clear();
		}

		void Add(const T& element)
		{
			Node* p = new Node;
			p->mData = element;
			p->mNext = null;

			if (mHead == null)
			{
				mTail = mHead = p;
			}
			else
			{
				mTail->mNext = p;
				mTail = p;
			}
		}

		void Remove(const T& element)
		{
			Node* p = mHead;
			Node* plast = mHead;

			while (p)
			{
				if (p->mData == element)
				{
					Node* willdel = p;
					p = p->mNext;

					if (willdel == mHead)
						mHead = p;

					if (willdel == mTail)
						mTail = p;

					if (mHead != mTail)
						plast->mNext = p;

					delete willdel;

					break;
				}

				plast = p;
				p = p->mNext;
			}
		}

		void Clear()
		{
			Node* p = mHead;

			while (p)
			{
				Node* willdel = p;
				p = p->mNext;
				delete willdel;
			}

			mHead = mTail = null;
		}

		class Iterator;

		Iterator First()
		{
			return Iterator(mHead);
		}

		Iterator Last()
		{
			return Iterator(null);
		}

		class Iterator
		{
		public:
			Iterator() : mNode(null) {}

			Iterator(Node* node)
			{
				mNode = node;
			}

			Iterator(const Iterator& it)
			{
				operator=(it);
			}

			Iterator& operator=(const Iterator& it)
			{
				mNode = it.mNode;
				return *this;
			}

			Iterator operator++()
			{
				mNode = mNode->mNext;
				return *this;
			}

			Iterator operator++(int dummy)
			{
				Node* last = mNode;
				mNode = mNode->mNext;
				return Iterator(last);
			}

			bool operator ==(const Iterator& it)
			{
				return mNode == it.mNode;
			}

			bool operator !=(const Iterator& it)
			{
				return !operator==(it);
			}

			T& operator*()
			{
				return (T&)(*mNode);
			}

			T* operator->()
			{
				return (T*)&(*mNode);
			}

		private:
			Node*	mNode;
		};

	private:
		Node*	mHead;
		Node*	mTail;
	};

	template <class Key, class T>
	class Map
	{
	public:
		struct Node
		{
			Key mKey;
			T mValue;
		};

		Map()
		{

		}

		~Map()
		{
			Clear();
		}

		class Iterator;

		Iterator Add(const Key& key)
		{
			Node node;
			node.mKey = key;
			mElemets.Add(node);

			int low = 0, high = mElemets.Length() - 1;
			qsort(low, high);

			return Find(key);
		}

		void Remove(const Iterator& it)
		{
			mElemets.Remove(*it);
		}

		Iterator Add(const Key& key, const T& value)
		{
			Node node;
			node.mKey = key;
			node.mValue = value;
			mElemets.Add(node);

			int low = 0, high = mElemets.Length() - 1;
			qsort(low, high);

			return Find(key);
		}

		T& operator[](const Key& key)
		{
			Iterator it = Find(key);
			if (it == Last())
			{
				it = Add(key);
				return (T&)it->mValue;
			}

			return (T&)it->mValue;
		}

		const T& operator[](const Key& key) const
		{
			return Find(key)->mValue;
		}

		Iterator First()
		{
			return Iterator(mElemets.Length() == 0 ? null : &mElemets[0]);
		}

		Iterator Last()
		{
			return Iterator(mElemets.Length() == 0 ? null : (&mElemets[mElemets.Length() - 1])+1);
		}

		void Clear()
		{
			mElemets.Clear();
		}


		Iterator Find(const Key& key)
		{
			if (mElemets.Length() == 0)
				return Last();

			int low = 0, high = mElemets.Length() - 1;
//			qsort(low, high);

			return BinarySearch(key, low, high);
		}


		Iterator BinarySearch(const Key& key, int low, int high)
		{
			while (low <= high)
			{
				int pivotloc = low + (high - low) / 2;

				if (key < mElemets[pivotloc].mKey)
					high = pivotloc - 1;
				else if (key > mElemets[pivotloc].mKey)
					low = pivotloc + 1;
				else if(key == mElemets[pivotloc].mKey)
					return Iterator(&mElemets[pivotloc]);
			}

			return Last();
		}

		void qsort(int low, int high)
		{
			if (low < high)
			{
				int pivotloc = partition(low, high);
				qsort(low, pivotloc - 1);
				qsort(pivotloc + 1, high);
			}
		}

	private:
		int partition(int low, int high)
		{
			Node t = mElemets[low];
			Key pivotkey = mElemets[low].mKey;
			while (low < high)
			{
				while (low < high && mElemets[high].mKey >= pivotkey) --high;
				mElemets[low] = mElemets[high];
				while (low < high && mElemets[low].mKey <= pivotkey) ++low;
				mElemets[high] = mElemets[low];
			}
			mElemets[low] = t;

			return low;
		}

		class Iterator
		{
		public:
			Iterator() : mNode(null) {}

			Iterator(Node* node)
			{
				mNode = node;
			}

			Iterator(const Iterator& it)
			{
				operator=(it);
			}

			Iterator& operator=(const Iterator& it)
			{
				mNode = it.mNode;
				return *this;
			}

			Iterator operator++()
			{
				return ++mNode;
			}

			Iterator operator++(int dummy)
			{
				return Iterator(mNode++);
			}

			bool operator ==(const Iterator& it)
			{
				return mNode == it.mNode;
			}

			bool operator !=(const Iterator& it)
			{
				return !operator==(it);
			}

			Node& operator*()
			{
				return (Node&)(*mNode);
			}

			Node* operator->()
			{
				return mNode;
			}

		private:
			Node*	mNode;
		};

	protected:
		Array<Node> mElemets;
	};


#define VgeDeclareSingleton(cls) \
public: \
	static cls& GetIns()


#define VgeImplementSingleton(cls) \
		cls& cls::GetIns() \
		{ \
			static cls ins; \
			return ins; \
		} \

}
