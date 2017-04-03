#include "Vge.h"

namespace Vge
{
	MemoryStream::MemoryStream()
		: mData(null)
		, mSize(0)
		, mCurPos(0)
	{
	}

	MemoryStream::MemoryStream( dword size )
		: mCurPos(0)
	{
		mData = new byte[size];
		mSize = size;
	}

	MemoryStream::MemoryStream( byte* data, dword size, bool managed /*= true*/ )
		: mCurPos(0)
	{
		if (managed)
			mData = data;
		else
		{
			mData = new byte[size];
			System::Memcpy(mData, data, size);
		}

		mSize = size;
	}

	MemoryStream::~MemoryStream()
	{
		if (mData)
			delete[] mData;
	}

	void MemoryStream::SetPos( dword pos )
	{
		mCurPos = pos;
	}

	void MemoryStream::Read( byte* data, dword size )
	{
		System::Memcpy( data, mData+mCurPos, size );
	}

	void MemoryStream::Write( byte* data, dword size )
	{
		System::Memcpy(mData+mCurPos, data, size);
	}

	dword MemoryStream::GetSize()
	{
		return mSize;
	}
}