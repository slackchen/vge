#pragma once

namespace Vge
{
	class VGE_API Name
	{
	public:
		Name();
		Name(const vchar* str);
		Name(const String& str);
		~Name();

		static void StaticInit();
		static void StaticUninit();

		String& GetString() const;

		bool operator == ( const Name& rhs ) const;

		bool operator != ( const Name& rhs ) const;

		Name& operator =( const String& str );

		operator dword() const;

	private:
		dword mIndex;

		void SetString( const vchar* str );
	};

}