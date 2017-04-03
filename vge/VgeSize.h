#pragma once

namespace Vge
{
	class VGE_API Size
	{
	public:
		int width;
		int height;

		Size() : width(0), height(0) {}
		Size(int w, int h) : width(w), height(h) {}
	};
}