#pragma once

namespace Vge
{
	class VGE_API Sprite
	{
	public:
		Sprite();
		virtual ~Sprite();

	protected:
		Vector2	mPos;		// Position on screen surface
		Vector2 mOrigin;	// Origin point of sprite
		float mScale;
	};
}