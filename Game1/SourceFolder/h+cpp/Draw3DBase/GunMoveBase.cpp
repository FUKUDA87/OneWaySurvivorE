
#include "GunMoveBase.h"

C_GunMoveBase::C_GunMoveBase()
{
	InitGun();
	SetGun(1);
}

C_GunMoveBase::~C_GunMoveBase()
{
	delete gunBase;
}

void C_GunMoveBase::InitGun(void)
{
	D3DXMatrixTranslation(&ConnectGunMat,0.0f,0.0f,0.0f);
}

bool C_GunMoveBase::UpdateGun()
{
	gunBase->Update(ConnectGunMat);
	return true;
}

bool C_GunMoveBase::UpdateGun(float AngX, float AngY)
{
	gunBase->Update(AngX, AngY, ConnectGunMat);
	return true;
}

bool C_GunMoveBase::UpdateGun(const D3DXMATRIX * CamMat)
{
	gunBase->Update(CamMat, ConnectGunMat);
	return true;
}

bool C_GunMoveBase::UpdateBullet(const BULLETRAYJUDG *BRJ)
{
	UpdateBM(BRJ->MoveVec, gunBase->GetBullet(BRJ->RayPos,BRJ->JudgRayFlg), gunBase->GetMuzFla(), &gunBase->GetGMat());
	return true;
}

bool C_GunMoveBase::UpdateBullet(const BULLETRAYJUDG *BRJ,const bool * BirthFlg)
{
	UpdateBM(BirthFlg, BRJ->MoveVec, gunBase->GetBullet(BRJ->RayPos, BRJ->JudgRayFlg), gunBase->GetMuzFla(), &gunBase->GetGMat());
	return true;
}

bool C_GunMoveBase::UpdateBullet(const BULLETRAYJUDG *BRJ,const bool * BirthFlg, const SoundCamera * sc)
{
	UpdateBM(BirthFlg, BRJ->MoveVec, gunBase->GetBullet(BRJ->RayPos, BRJ->JudgRayFlg), gunBase->GetMuzFla(), &gunBase->GetGMat(), sc);
	return true;
}

bool C_GunMoveBase::UpdateBullet(const BULLETRAYJUDG *BRJ, const bool * KeyFlg, const bool * BirthFlg, const SoundCamera * sc)
{
	UpdateBM(KeyFlg, BirthFlg, BRJ->MoveVec, gunBase->GetBullet(BRJ->RayPos, BRJ->JudgRayFlg), gunBase->GetMuzFla(), &gunBase->GetGMat(), sc);
	return true;
}

bool C_GunMoveBase::UpdateBulletMove(void)
{
	UpdateBM();
	return true;
}

void C_GunMoveBase::Draw3DGun()
{
	DrawBM();
	gunBase->Draw3D();
}

//D3DXMATRIX C_GunMoveBase::GetDrawMatGun(void)
//{
//	return D3DXMATRIX();
//}

void C_GunMoveBase::SetGun(int GunNo)
{
	gunBase = gunManager.GetGun(GunNo,ConnectGunMat);
}

