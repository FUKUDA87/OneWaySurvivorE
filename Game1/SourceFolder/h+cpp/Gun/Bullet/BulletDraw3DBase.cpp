#include "BulletDraw3DBase.h"

C_BulletDraw3DBase::C_BulletDraw3DBase(const GETGUNDATA * GetGunData)
{
	//InitHitRayPos(&GetGunData->HitRayFlg, &GetGunData->HitRayPos);
	InitCount(&GetGunData->InitCountMax);
	Speed = GetGunData->Speed;
}

void C_BulletDraw3DBase::InitHitRayPos(const bool *HitRayFlg, const D3DXVECTOR3 * HitRayPos)
{
	if (*HitRayFlg != true) return;

	//’e‚ªÆ€‚Ì•û‚ÉŒü‚©‚¤ˆ—
	double Ang, ang = 0.0f;
	judg.CroDot(Bullet.Mat, &Bullet.Rot, *HitRayPos, D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Ang, ang, false);
	Bullet.Mat = Bullet.Rot* Bullet.Mat;
}

void C_BulletDraw3DBase::InitCount(const int * InitCountMax)
{
	NowCount = CountMax = *InitCountMax;
}

bool C_BulletDraw3DBase::CountUpdate(void)
{
	NowCount -= 1;
	if (NowCount < 0) {
		NowCount = 0;
		return false;
	}
	return true;
}
