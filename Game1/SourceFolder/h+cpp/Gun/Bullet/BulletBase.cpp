#include "BulletBase.h"

void BulletBase::Init()
{
	NowCount = 0;
	BulletRayFlg = true;
}

BulletBase::BulletBase()
{
	Init();
}

float BulletBase::GetMoVecDis()
{
	/*D3DXMATRIX Mat;
	Mat = bul.Base.Trans*bul.Base.Mat;
	judg.MatMatVec(&MoveVec, bul.Base.Mat, Mat);
	return D3DXVec3Length(&MoveVec);*/
	return MoveSize;
}

bool BulletBase::UpdateTime(void)
{
	NowCount -= 1;
	if (NowCount < 0) {
		NowCount = 0;
		return false;
	}
	return true;
}

bool BulletBase::GetRayFlg(void)
{
	return BulletRayFlg;
}

void BulletBase::SetRayFlg(const bool * Flg)
{
	if (BulletRayFlg == true) {
		BulletRayFlg = *Flg;
	}
}
