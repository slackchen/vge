#include "Vge.h"

namespace Vge
{
	const int BUF_SIZE = 65536;

	FileStream::FileStream( const vchar* filename )
		: mHandle( NULL )
		, mMapFile( NULL )
		, mData( NULL )
		, mCurPos( 0 )
	{
		DWORD dwAccessFlag = GENERIC_READ | GENERIC_WRITE, dwCreateFlag = OPEN_EXISTING, dwProtected = PAGE_READWRITE;

		mHandle = (handle)::CreateFile( filename, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

		dword size = GetSize();

		if ( INVALID_HANDLE_VALUE == mHandle )
		{
			mHandle = (handle)::CreateFile( filename, GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

			size = 1;
		}

		if ( INVALID_HANDLE_VALUE == mHandle )
			return;

		if ( size == 0 ) size = 1;
		mMapFile = ::CreateFileMapping( mHandle, NULL, PAGE_READWRITE, 0, size, NULL );
		if ( NULL == mMapFile )
		{
			::CloseHandle( mHandle );
			mHandle = NULL;
			return;
		}

		mData = (byte*) MapViewOfFile( mMapFile, FILE_MAP_ALL_ACCESS, 0, mCurPos, size );
	}

	FileStream::~FileStream()
	{
		::UnmapViewOfFile( mData );
		::CloseHandle( mMapFile );
		::CloseHandle( mHandle );
	}

	void FileStream::SetPos(dword pos)
	{
		mCurPos = pos;
	}

	void FileStream::Resize(dword newsize, bool discard /*= false*/)
	{
		if ( GetSize() >= newsize )
			return;

		if ( mData )
		{
			::UnmapViewOfFile( mData );
			mData = NULL;
		}

		if ( mMapFile )
		{
			::CloseHandle( mMapFile );
			mMapFile = NULL;
		}

		mMapFile = ::CreateFileMapping( mHandle, NULL, PAGE_READWRITE, 0, newsize, NULL );
		if ( NULL == mMapFile )
		{
			::CloseHandle( mHandle );
			mHandle = NULL;
			return;
		}

		mData = (byte*) MapViewOfFile( mMapFile, FILE_MAP_ALL_ACCESS, 0, 0, newsize );
	}

	void FileStream::Read(byte* data, dword size)
	{
		System::Memcpy( data, mData + mCurPos, size );
		SetPos( mCurPos + size );
	}

	void FileStream::Write(byte* data, dword size)
	{
		Resize(mCurPos + size);

		System::Memcpy( mData + mCurPos, data, size );
		SetPos( mCurPos + size );
	}

	dword FileStream::GetSize()
	{
		return ::GetFileSize( (HWND)mHandle, NULL );
	}

	void FileStream::WriteUnicodeFlag()
	{
		word flag = 0xfeff;
		Write( (byte*)&flag, sizeof(word) );
	}
}