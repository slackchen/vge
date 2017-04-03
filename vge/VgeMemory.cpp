#include "Vge.h"

namespace Vge
{

	MallocWindows	MallocWindow;
	BOOL			MallocFirst = TRUE;

	void* Memory::Allocate(size_t size)
	{
		if (MallocFirst)
		{
			MallocWindow.Init(TRUE);
			MallocFirst = FALSE;
		}

		return MallocWindow.Malloc((DWORD)size);
		//return ::VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	}

	void Memory::Deallocate(void* p)
	{
		MallocWindow.Free(p);
		//::VirtualFree(p, 0, MEM_RELEASE);
	}
}
