#pragma once

namespace Vge
{
	class VGE_API Memory
	{
	public:
		static void* Allocate(size_t size);

		static void Deallocate(void* p);
	};

#define MEM_TIME(st)
#define checkSlow(x)
#define check(x)
#define STAT(x) x
#define verify(x)

inline void debugf(...)
{}
	//
	// Optimized Windows virtual memory allocator.
	//
	class MallocWindows
	{
	private:
		// Counts.
		enum {POOL_COUNT = 43     };
		enum {POOL_MAX   = 32768+1};

		// Forward declares.
		struct FreeMem;
		struct PoolTable;

		// Memory pool info. 32 bytes.
		struct PoolInfo
		{
			DWORD	    mBytes;		// Bytes allocated for pool.
			DWORD		mOsBytes;	// Bytes aligned to page size.
			DWORD       mTaken;      // Number of allocated elements in this pool, when counts down to zero can free the entire pool.
			BYTE*       mMem;		// Memory base.
			PoolTable* mTable;		// Index of pool.
			FreeMem*   mFirstMem;   // Pointer to first free memory in this pool.
			PoolInfo*	mNext;
			PoolInfo**	mPrevLink;

			void Link( PoolInfo*& before )
			{
				if( before )
					before->mPrevLink = &mNext;
				mNext     = before;
				mPrevLink = &before;
				before   = this;
			}
			void Unlink()
			{
				if( mNext )
					mNext->mPrevLink = mPrevLink;
				*mPrevLink = mNext;
			}
		};

		// Information about a piece of free memory. 8 bytes.
		struct FreeMem
		{
			FreeMem*	mNext;		// Next or MemLastPool[], always in order by pool.
			DWORD		mBlocks;		// Number of consecutive free blocks here, at least 1.
			PoolInfo* GetPool()
			{
				return (PoolInfo*)((INT)this & 0xffff0000);
			}
		};

		// Pool table.
		struct PoolTable
		{
			PoolInfo* mFirstPool;
			PoolInfo* mExaustedPool;
			DWORD     mBlockSize;
		};

		// Variables.
		PoolTable  mPoolTable[POOL_COUNT], mOsTable;
		PoolInfo*	mPoolIndirect[256];
		PoolTable* mMemSizeToPoolTable[POOL_MAX];
		INT         mMemInit;
		INT			mOsCurrent,mOsPeak,mUsedCurrent,mUsedPeak,mCurrentAllocs,mTotalAllocs;
		DOUBLE		mMemTime;
		DWORD		mGPageSize;

		// Implementation.
		void OutOfMemory()
		{
			//appErrorf( *LocalizeError("OutOfMemory",TEXT("Core")) );
		}
		PoolInfo* CreateIndirect()
		{
			PoolInfo* Indirect = (PoolInfo*)VirtualAlloc( NULL, 256*sizeof(PoolInfo), MEM_COMMIT, PAGE_READWRITE );
			if( !Indirect )
				OutOfMemory();
			return Indirect;
		}

	public:
		// FMalloc interface.
		MallocWindows()
			:	mMemInit( 0 )
			,	mOsCurrent		( 0 )
			,	mOsPeak			( 0 )
			,	mUsedCurrent		( 0 )
			,	mUsedPeak		( 0 )
			,	mCurrentAllocs	( 0 )
			,	mTotalAllocs		( 0 )
			,	mMemTime			( 0.0 )
			,	mGPageSize		(4096)
		{}
		void* Malloc( DWORD size )
		{
			checkSlow(size>=0);
			checkSlow(mMemInit);
			MEM_TIME(mMemTime -= appSeconds());
			STAT(mCurrentAllocs++);
			STAT(mTotalAllocs++);
			FreeMem* tofree;
			if( size<POOL_MAX )
			{
				// Allocate from pool.
				PoolTable* table = mMemSizeToPoolTable[size];
				checkSlow(size<=table->mBlockSize);
				PoolInfo* pool = table->mFirstPool;
				if( !pool )
				{
					// Must create a new pool.
					DWORD blocks  = 65536 / table->mBlockSize;
					DWORD bytes   = blocks * table->mBlockSize;
					checkSlow(blocks>=1);
					checkSlow(blocks*table->mBlockSize<=bytes);

					// Allocate memory.
					tofree = (FreeMem*)VirtualAlloc( NULL, bytes, MEM_COMMIT, PAGE_READWRITE );
					if( !tofree )
						OutOfMemory();

					// Create pool in the indirect table.
					PoolInfo*& Indirect = mPoolIndirect[((DWORD)tofree>>24)];
					if( !Indirect )
						Indirect = CreateIndirect();
					pool = &Indirect[((DWORD)tofree>>16)&255];

					// Init pool.
					pool->Link( table->mFirstPool );
					pool->mMem            = (BYTE*)tofree;
					pool->mBytes		     = bytes;
					pool->mOsBytes		 = Align(bytes,mGPageSize);
					STAT(mOsPeak = Math::Max(mOsPeak,mOsCurrent+=pool->mOsBytes));
					pool->mTable		     = table;
					pool->mTaken			 = 0;
					pool->mFirstMem       = tofree;

					// Create first free item.
					tofree->mBlocks         = blocks;
					tofree->mNext           = NULL;
				}

				// Pick first available block and unlink it.
				pool->mTaken++;
				checkSlow(pool->mFirstMem);
				checkSlow(pool->mFirstMem->mBlocks>0);
				tofree = (FreeMem*)((BYTE*)pool->mFirstMem + --pool->mFirstMem->mBlocks * table->mBlockSize);
				if( pool->mFirstMem->mBlocks==0 )
				{
					pool->mFirstMem = pool->mFirstMem->mNext;
					if( !pool->mFirstMem )
					{
						// Move to exausted list.
						pool->Unlink();
						pool->Link( table->mExaustedPool );
					}
				}
				STAT(mUsedPeak = Math::Max(mUsedPeak,mUsedCurrent+=table->mBlockSize));
			}
			else
			{
				// Use OS for large allocations.
				INT alignedSize = Align(size,mGPageSize);
				tofree = (FreeMem*)VirtualAlloc( NULL, alignedSize, MEM_COMMIT, PAGE_READWRITE );
				if( !tofree )
					OutOfMemory();
				checkSlow(!((SIZE_T)tofree&65535));

				// Create indirect.
				PoolInfo*& indirect = mPoolIndirect[((DWORD)tofree>>24)];
				if( !indirect )
					indirect = CreateIndirect();

				// Init pool.
				PoolInfo* Pool = &indirect[((DWORD)tofree>>16)&255];
				Pool->mMem		= (BYTE*)tofree;
				Pool->mBytes		= size;
				Pool->mOsBytes	= alignedSize;
				Pool->mTable		= &mOsTable;
				STAT(mOsPeak   = Math::Max(mOsPeak,  mOsCurrent+=alignedSize));
				STAT(mUsedPeak = Math::Max(mUsedPeak,mUsedCurrent+=size));
			}
			MEM_TIME(mMemTime += appSeconds());
			return tofree;
		}
		void* Realloc( void* ptr, DWORD newSize )
		{
			checkSlow(mMemInit);
			MEM_TIME(mMemTime -= appSeconds());
			check(newSize>=0);
			void* newPtr = ptr;
			if( ptr && newSize )
			{
				checkSlow(mMemInit);
				PoolInfo* pool = &mPoolIndirect[(DWORD)ptr>>24][((DWORD)ptr>>16)&255];
				if( pool->mTable!=&mOsTable )
				{
					// Allocated from pool, so grow or shrink if necessary.
					if( newSize>pool->mTable->mBlockSize || mMemSizeToPoolTable[newSize]!=pool->mTable )
					{
						newPtr = Malloc( newSize );
						System::Memcpy( newPtr, ptr, Math::Min(newSize,pool->mTable->mBlockSize) );
						Free( ptr );
					}
				}
				else
				{
					// Allocated from OS.
					checkSlow(!((INT)ptr&65535));
					if( newSize>pool->mOsBytes || newSize*3<pool->mOsBytes*2 )
					{
						// Grow or shrink.
						newPtr = Malloc( newSize );
						System::Memcpy( newPtr, ptr, Math::Min(newSize,pool->mBytes) );
						Free( ptr );
					}
					else
					{
						// Keep as-is, reallocation isn't worth the overhead.
						pool->mBytes = newSize;
					}
				}
			}
			else if( ptr == NULL )
			{
				newPtr = Malloc( newSize );
			}
			else
			{
				Free( ptr );
				newPtr = NULL;
			}
			MEM_TIME(mMemTime += appSeconds());
			return newPtr;
		}
		void Free( void* ptr )
		{
			if( !ptr )
				return;
			checkSlow(mMemInit);
			MEM_TIME(mMemTime -= appSeconds());
			STAT(mCurrentAllocs--);

			// Windows version.
			PoolInfo* pool = &mPoolIndirect[(DWORD)ptr>>24][((DWORD)ptr>>16)&255];
			checkSlow(pool->mBytes!=0);
			if( pool->mTable!=&mOsTable )
			{
				// If this pool was exausted, move to available list.
				if( !pool->mFirstMem )
				{
					pool->Unlink();
					pool->Link( pool->mTable->mFirstPool );
				}

				// Free a pooled allocation.
				FreeMem* tofree		= (FreeMem *)ptr;
				tofree->mBlocks		= 1;
				tofree->mNext			= pool->mFirstMem;
				pool->mFirstMem		= tofree;
				STAT(mUsedCurrent   -= pool->mTable->mBlockSize);

				// Free this pool.
				checkSlow(pool->mTaken>=1);
				if( --pool->mTaken == 0 )
				{
					// Free the OS memory.
					pool->Unlink();
					verify( VirtualFree( pool->mMem, 0, MEM_RELEASE )!=0 );
					STAT(mOsCurrent -= pool->mOsBytes);
				}
			}
			else
			{
				// Free an OS allocation.
				checkSlow(!((INT)ptr&65535));
				STAT(mUsedCurrent -= pool->mBytes);
				STAT(mOsCurrent   -= pool->mOsBytes);
				verify( VirtualFree( ptr, 0, MEM_RELEASE )!=0 );
			}
			MEM_TIME(mMemTime += appSeconds());
		}
		/**
		* Gathers memory allocations for both virtual and physical allocations.
		*
		* @param Virtual	[out] size of virtual allocations
		* @param Physical	[out] size of physical allocations	
		*/
		void GetAllocationInfo( SIZE_T& virtualmem, SIZE_T& physical )
		{
			virtualmem	= mOsCurrent;
			physical	= 0;
		}
		void DumpAllocs()
		{
			MallocWindows::HeapCheck();

			STAT(debugf( TEXT("Memory Allocation Status") ));
			STAT(debugf( TEXT("Curr Memory % 5.3fM / % 5.3fM"), mUsedCurrent/1024.0/1024.0, mOsCurrent/1024.0/1024.0 ));
			STAT(debugf( TEXT("Peak Memory % 5.3fM / % 5.3fM"), mUsedPeak   /1024.0/1024.0, mOsPeak   /1024.0/1024.0 ));
			STAT(debugf( TEXT("Allocs      % 6i Current / % 6i Total"), mCurrentAllocs, mTotalAllocs ));
			MEM_TIME(debugf( "Seconds     % 5.3f", mMemTime ));
			MEM_TIME(debugf( "MSec/Allc   % 5.5f", 1000.0 * mMemTime / MemAllocs ));

#if STATS
			if( ParseParam(appCmdLine(), TEXT("MEMSTAT")) )
			{
				debugf( TEXT("Block Size Num Pools Cur Allocs Total Allocs Mem Used Mem Waste Efficiency") );
				debugf( TEXT("---------- --------- ---------- ------------ -------- --------- ----------") );
				INT totalPoolCount  = 0;
				INT totalAllocCount = 0;
				INT totalMemUsed    = 0;
				INT totalMemWaste   = 0;
				for( INT i=0; i<POOL_COUNT; i++ )
				{
					PoolTable* table = &mPoolTable[i];
					INT poolCount=0;
					INT allocCount=0;
					INT memUsed=0;
					for( INT i=0; i<2; i++ )
					{
						for( PoolInfo* Pool=(i?table->mFirstPool:table->mExaustedPool); Pool; Pool=Pool->mNext )
						{
							poolCount++;
							allocCount += Pool->mTaken;
							memUsed += Pool->mBytes;
							INT FreeCount=0;
							for( FreeMem* Free=Pool->mFirstMem; Free; Free=Free->mNext )
								FreeCount += Free->mBlocks;
						}
					}
					INT memWaste = memUsed - allocCount*table->mBlockSize;
					debugf
						(
						TEXT("% 10i % 9i % 10i % 11iK % 7iK % 8iK % 9.2f%%"),
						table->mBlockSize,
						poolCount,
						allocCount,
						0,
						memUsed /1024,
						memWaste/1024,
						memUsed ? 100.0 * memUsed / (memUsed+memWaste) : 100.0
						);
					totalPoolCount  += poolCount;
					totalAllocCount += allocCount;
					totalMemUsed    += memUsed;
					totalMemWaste   += memWaste;
				}
				debugf
					(
					TEXT("BlkOverall % 9i % 10i % 11iK % 7iK % 8iK % 9.2f%%"),
					totalPoolCount,
					totalAllocCount,
					0,
					totalMemUsed /1024,
					totalMemWaste/1024,
					totalMemUsed ? 100.0 * totalMemUsed / (totalMemUsed+totalMemWaste) : 100.0
					);
			}
#endif
		}
		void HeapCheck()
		{
			for( INT i=0; i<POOL_COUNT; i++ )
			{
				PoolTable* table = &mPoolTable[i];
				for( PoolInfo** poolPtr=&table->mFirstPool; *poolPtr; poolPtr=&(*poolPtr)->mNext )
				{
					PoolInfo* pool=*poolPtr;
					check(pool->mPrevLink==poolPtr);
					check(pool->mFirstMem);
					for( FreeMem* tofree=pool->mFirstMem; tofree; tofree=tofree->mNext )
						check(tofree->mBlocks>0);
				}
				for( PoolInfo** poolPtr=&table->mExaustedPool; *poolPtr; poolPtr=&(*poolPtr)->mNext )
				{
					PoolInfo* pool=*poolPtr;
					check(pool->mPrevLink==poolPtr);
					check(!pool->mFirstMem);
				}
			}
		}
		void Init( BOOL Reset )
		{
			check(!mMemInit);
			mMemInit = 1;

			// Get OS page size.
#ifndef XBOX
			SYSTEM_INFO si;
			GetSystemInfo( &si );
			mGPageSize = si.dwPageSize;
			check(!(mGPageSize&(mGPageSize-1)));
#else
			mGPageSize = 4096;
#endif

			// Init tables.
			mOsTable.mFirstPool    = NULL;
			mOsTable.mExaustedPool = NULL;
			mOsTable.mBlockSize    = 0;

			mPoolTable[0].mFirstPool    = NULL;
			mPoolTable[0].mExaustedPool = NULL;
			mPoolTable[0].mBlockSize    = 8;
			for( DWORD i=1; i<6; i++ )
			{
				mPoolTable[i].mFirstPool    = NULL;
				mPoolTable[i].mExaustedPool = NULL;
				mPoolTable[i].mBlockSize    = (8<<(i>>2)) + (2<<(i-1));
			}
			for( DWORD i=6; i<POOL_COUNT; i++ )
			{
				mPoolTable[i].mFirstPool    = NULL;
				mPoolTable[i].mExaustedPool = NULL;
				mPoolTable[i].mBlockSize    = (4+((i+6)&3)) << (1+((i+6)>>2));
			}
			for( DWORD i=0; i<POOL_MAX; i++ )
			{
				DWORD index;
				for( index=0; mPoolTable[index].mBlockSize<i; index++ );
				checkSlow(index<POOL_COUNT);
				mMemSizeToPoolTable[i] = &mPoolTable[index];
			}
			for( DWORD i=0; i<256; i++ )
			{
				mPoolIndirect[i] = NULL;
			}
			check(POOL_MAX-1==mPoolTable[POOL_COUNT-1].mBlockSize);
		}
		void Exit()
		{
			check(mMemInit);
			mMemInit = 0;
		}
	};

	/*-----------------------------------------------------------------------------
	The End.
	-----------------------------------------------------------------------------*/
}

#ifdef VGE_MEMORY_MANAGEMENT

inline void* operator new(size_t size)
{
	return Vge::Memory::Allocate(size);
}

inline void operator delete(void * p)
{
	return Vge::Memory::Deallocate(p);
}

inline void* operator new[](size_t size)
{
	return Vge::Memory::Allocate(size);
}

inline void operator delete[](void * p)
{
	return Vge::Memory::Deallocate(p);
}

#endif // VGE_MEMORY_MANAGEMENT