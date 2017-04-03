#pragma once

namespace Vge
{
	class VGE_API VgeException
	{
	public:
		VgeException(const String& whatstr);

		virtual ~VgeException();

		const String& What() const;

		static void ThrowException(const String& str, const String& file, int line);

	private:
		String	mWhat;
	};
}

#ifdef VGE_UNICODE
#	define VGE_THROW(str) Vge::VgeException::ThrowException(str, __WFILE__, __LINE__)
#else
#	define VGE_THROW(str) Vge::VgeException::ThrowException(str, __FILE__, __LINE__)
#endif
