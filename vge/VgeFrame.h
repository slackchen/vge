#pragma once

namespace Vge
{
	class VGE_API Frame : public Runable
	{
	public:
		Frame();
		virtual ~Frame();

		virtual bool Run(Window* window);

		virtual int Run();

	protected:
		Window* mWindow;
	};
}
