#include "Vge.h"

namespace Vge
{
	/* magic numbers from http://www.isthe.com/chongo/tech/comp/fnv/ */ 
	static const dword InitialFNV = 2166136261U; 
	static const dword FNVMultiple = 16777619;

	/* Fowler / Noll / Vo (FNV) Hash */ 
	dword Vge_Hash(const String &s) 
	{ 
		dword hash = InitialFNV; 
		for(dword i = 0; i < s.Length(); i++) 
		{ 
			hash = hash ^ (s[i]);       /* xor  the low 8 bits */ 
			hash = hash * FNVMultiple;  /* multiply by the magic number */ 
		} 
		return hash; 
	} 

	struct NameInfo
	{
		dword mHashPos;
		dword mIndex;
		String* mNameStr;
		NameInfo* mNext;
	};

	const int cHashSize = 65536;

	NameInfo* gNameInfos[cHashSize];
	Array<NameInfo*> gNames;
	dword gEmptyHashPos = 0;

	void Name::StaticInit()
	{
		for ( int i = 0; i < cHashSize; ++i )
			gNameInfos[i] = null;
	}

	void Name::StaticUninit()
	{
		for ( int i = 0; i < cHashSize; ++i )
		{
			NameInfo* naminfo = gNameInfos[i];
			while ( null != naminfo )
			{
				NameInfo* curinfo = naminfo;
				naminfo = naminfo->mNext;

				delete curinfo->mNameStr;
				delete curinfo;
			}

		}

		gNames.Clear();
	}

	Name::Name()
	{
		SetString(VT(""));
	}

	Name::Name(const vchar* str)
	{
		SetString( str );
	}

	Name::Name( const String& str )
	{
		SetString( str.Str() );
	}
	Name::~Name()
	{

	}

	void Name::SetString(const vchar* str)
	{
		// Make hash position
		dword hashpos = Vge_Hash(str) & ( cHashSize - 1 );

		// Process conflict
		NameInfo* nameinfo = gNameInfos[hashpos];

		while ( null != nameinfo )
		{
			if ( System::Stricmp((*nameinfo->mNameStr).Str(), str ) == 0 )
			{
				mIndex = nameinfo->mIndex;
				return;
			}

			nameinfo = nameinfo->mNext;
		}

		mIndex = gNames.Length();

		// Not found, make a new name info
		NameInfo* oldinfo = nameinfo;

		nameinfo = new NameInfo;
		nameinfo->mHashPos = hashpos;
		nameinfo->mNameStr = new String(str);
		nameinfo->mIndex = mIndex;
		nameinfo->mNext = null;

		if (oldinfo)
			oldinfo->mNext = nameinfo;
		else
			gNameInfos[hashpos] = nameinfo;

		gNames.Add(nameinfo);
	}

	String& Name::GetString() const
	{
		return *(gNames[mIndex]->mNameStr);
	}

	bool Name::operator ==( const Name& rhs ) const
	{
		return mIndex == rhs.mIndex;
	}

	bool Name::operator !=( const Name& rhs ) const
	{
		return mIndex != rhs.mIndex;
	}

	Name& Name::operator=( const String& str )
	{
		SetString(str.Str());
		return *this;
	}

	Name::operator dword() const
	{
		return mIndex;
	}
}