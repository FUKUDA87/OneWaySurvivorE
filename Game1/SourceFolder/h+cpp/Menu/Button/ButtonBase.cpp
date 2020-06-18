#include "ButtonBase.h"
#include"../../GameSource/Judgment.h"

c_ButtonBase::c_ButtonBase()
{
	nextNo = 0;
}

bool c_ButtonBase::Update(const D3DXVECTOR3 * pos)
{
	basePos = *pos;
	Pos = basePos + transPos;

	return true;
}

bool c_ButtonBase::TouchJudg(void)
{
	Judg judg;
	return judg.PlaneCri(Pos, scalX, scalY, width, height);
}
