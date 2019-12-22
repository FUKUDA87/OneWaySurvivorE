#include "GunEA.h"

void GunEA::InitE()
{
	Pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	xfileManager.GetXfile(&gun.Mesh, "../GameFolder/Material/XFile/gun2EC.x");
	D3DXMatrixTranslation(&GmMat, 0.0f, 0.03f, 0.75f);
}

GunEA::GunEA(D3DXMATRIX Mat) :GunPA(Mat)
{
	InitE();
	D3DXMatrixTranslation(&gun.Base.Mat, Mat._41 + Pos.x, Mat._42 + Pos.y, Mat._43 + Pos.z);
}

bool GunEA::Update(D3DXMATRIX Mat)
{
	gun.Base.Mat = Mat;
	return true;
}

BulletEA * GunEA::GetBullet()
{
	D3DXVECTOR3 EPos;//‰¼
	return new BulletEA(gun.Base.Mat, GmMat, EPos, false);
}
