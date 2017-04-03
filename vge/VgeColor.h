#pragma once

namespace Vge
{
	class VGE_API Color
	{
	public:
		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;

		float r, g, b, a;

		Color();

		Color(float red, float green, float blue);

		Color(float red, float green, float blue, float alpha);

		Color(byte red, byte green, byte blue);

		Color(byte red, byte green, byte blue, byte alpha);

		operator dword() const;

		inline void FromRGBColor(byte red, byte green, byte blue);
		inline void FromRGBAColor(byte red, byte green, byte blue, byte alpha);
	};
}
