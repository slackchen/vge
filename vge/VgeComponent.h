#pragma once

namespace Vge
{
	class VGE_API Component/* : public Object*/
	{
	public:
		enum ClassGroup
		{
			CG_Actor = 1,
			CG_Scene,
			CG_Net,
			CG_Renderer,
		};

		virtual ~Component() {}

		bool Load();
	};
}