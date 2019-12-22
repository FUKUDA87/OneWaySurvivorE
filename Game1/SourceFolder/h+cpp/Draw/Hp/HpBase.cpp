#include "HpBase.h"

void C_HpBase::GetGage(const int * NowHp, const int * MaxHp)
{
	int s = *NowHp,e= *MaxHp;
	if (s > e)s = e;
	if (s < 0)s = 0;
	Per = ((float)s) / ((float)e);
	if (Per < 0.0f) {
		Per = 0.0f;
	}
}

D3DXVECTOR3 C_HpBase::GetTexPos(const D3DXVECTOR2 * TexPos, const D3DXVECTOR3 * TransPos, const D3DXVECTOR3 * ScalPos)
{
	D3DXVECTOR3 Pos;
	Pos.x = TransPos->x - (TexPos->x*ScalPos->x / 2.0f);
	Pos.y = TransPos->y - (TexPos->y*ScalPos->y / 2.0f);
	Pos.z = 0.0f;
	return Pos;
}
