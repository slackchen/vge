#include "Vge.h"

namespace Vge
{
	VgeException::VgeException( const String& whatstr )
	{
		mWhat = whatstr;
	}

	VgeException::~VgeException()
	{
	}

	const String& VgeException::What() const
	{
		return mWhat;
	}

	void VgeException::ThrowException(const String& str, const String& file, int line)
	{
		throw VgeException(VT("File: ") + file + VT(" Line: ") + line + VT(".\n") + str);
	}

}
