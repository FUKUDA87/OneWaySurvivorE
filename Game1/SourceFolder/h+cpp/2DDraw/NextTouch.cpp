#include "NextTouch.h"

C_NextTouch::C_NextTouch()
{
	InitTouch();
}

C_NextTouch::~C_NextTouch()
{
}

void C_NextTouch::InitTouch()
{
	DrawNum = 0;
}

bool C_NextTouch::UpdateAll(void)
{
	return false;
}

void C_NextTouch::Draw2DAll(void)
{
}

int C_NextTouch::TouchNow(void)
{
	return 0;
}

int C_NextTouch::TouchNow2(void)
{
	return 0;
}
