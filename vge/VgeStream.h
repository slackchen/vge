#pragma once

namespace Vge
{
	class VGE_API Stream
	{
	public:
		virtual ~Stream() = 0 {};

		virtual void SetPos(dword pos) = 0;

		virtual void Read(byte* data, dword size) = 0;

		virtual void Write(byte* data, dword size) = 0;

		virtual dword GetSize() = 0;


	protected:
	};

	class VGE_API MemoryStream : public Stream
	{
	public:
		MemoryStream();

		MemoryStream(byte* data, dword size, bool managed = false);

		MemoryStream(dword size);

		virtual ~MemoryStream();

		virtual void SetPos(dword pos);

		virtual void Read(byte* data, dword size);

		virtual void Write(byte* data, dword size);

		virtual dword GetSize();

	protected:
		byte* mData;
		dword mSize;
		dword mCurPos;
	};

	class VGE_API FileStream : public Stream
	{
	public:

		FileStream( const vchar* filename );
		virtual ~FileStream();

		virtual void SetPos(dword pos);

		virtual void Read(byte* data, dword size);

		virtual void Write(byte* data, dword size);

		virtual dword GetSize();

		void WriteUnicodeFlag();

	protected:
		void Resize(dword newsize, bool discard = false);

		handle	mHandle;
		handle	mMapFile;
		byte*	mData;
		dword	mCurPos;
	};
}