#include "Vge.h"

using namespace Vge;

bool Vge_Init()
{
	Name::StaticInit();

	return true;
}

void Vge_Uninit()
{
	Name::StaticUninit();
}