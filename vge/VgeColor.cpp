#include "Vge.h"

namespace Vge
{
	const Color Color::White	= Color(1.0f, 1.0f, 1.0f);
	const Color Color::Black	= Color(0.0f, 0.0f, 0.0f);
	const Color Color::Red		= Color(1.0f, 0.0f, 0.0f);
	const Color Color::Green	= Color(0.0f, 1.0f, 0.0f);
	const Color Color::Blue		= Color(0.0f, 0.0f, 1.0f);
	const Color Color::Yellow	= Color(1.0f, 1.0f, 0.0f);
	const Color Color::Magenta	= Color(1.0f, 0.0f, 1.0f);
	const Color Color::Cyan		= Color(0.0f, 1.0f, 1.0f);

	Color::Color():
		r(1.0f), g(1.0f), b(1.0f), a(1.0f)
	{
	}

	Color::Color(float red, float green, float blue):
		r(red), g(green), b(blue), a(1.0f)
	{
	}

	Color::Color(float red, float green, float blue, float alpha):
		r(red), g(green), b(blue), a(alpha)
	{
	}

	Color::Color(byte red, byte green, byte blue)
	{
		FromRGBColor(red, green, blue);
	}

	Color::Color(byte red, byte green, byte blue, byte alpha)
	{
		FromRGBAColor(red, green, blue, alpha);
	}

	Color::operator dword() const
	{
		return ((dword)(byte)(a * 255.0f) << 24) |
			((dword)(byte)(r * 255.0f) << 16) |
			((word)(byte)(g * 255.0f) << 8) |
			((byte)(b * 255.0f));	
	}

	void Color::FromRGBColor(byte red, byte green, byte blue)
	{
		r = (float)red / 255.0f;
		g = (float)green / 255.0f;
		b = (float)blue	/ 255.0f;
		a = 1.0f;
	}

	void Color::FromRGBAColor(byte red, byte green, byte blue, byte alpha)
	{
		r = (float)red / 255.0f;
		g = (float)green / 255.0f;
		b = (float)blue	/ 255.0f;
		a = (float)alpha / 255.0f;
	}
}
