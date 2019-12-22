#include "Bill1.h"

void Bill::SuperUpdate()
{
	Update();
	WaUpdate();
}

void Bill::SuperDraw()
{
	Draw();
	WaDraw();
}
