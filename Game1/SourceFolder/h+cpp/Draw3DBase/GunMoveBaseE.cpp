#include "GunMoveBaseE.h"

C_GunMoveBaseE::C_GunMoveBaseE()
{
	InitGun();
}

C_GunMoveBaseE::~C_GunMoveBaseE()
{
	delete gunEA;

	delete GunMove;
}

void C_GunMoveBaseE::InitGun(void)
{
	gunEA = new GunEA(gun.ConnectMat);

	GunMove = new C_GunLockonA();

	//\‘¢‘Ì‚Ì‰Šú‰»
	gun.NowBase.AngX = 0.0f;
	gun.NowBase.AngY = 0.0f;
	D3DXMatrixRotationX(&gun.NowBase.RotX, D3DXToRadian((float)gun.NowBase.AngX));
	D3DXMatrixRotationY(&gun.NowBase.RotY, D3DXToRadian((float)gun.NowBase.AngY));
	gun.BulletFlg = false;
	gun.EndFlg = false;
	gun.GunMoveFlg = false;
	gun.NowAnime = 0.0f;
	gun.AIFlg = false;
	gun.NowBase.Flg = true;
	gun.RayCountInit = 30;
	gun.GunMoveEndFlg = false;

	gun.RayJudgFlg = false;
}

void C_GunMoveBaseE::InitGunMove(void)
{
	gun.Start.RotXMat = gun.NowBase.RotX;
	gun.Start.RotYMat = gun.NowBase.RotY;

	gun.NowBase.TraPos = gunEA->GetPos();
	judgg.SetTransMat(&gun.NowBase.Trans, &gun.NowBase.TraPos);
	gun.NowBase.Mat = gun.NowBase.Trans*gun.ConnectMat;

	D3DXMATRIX End;
	judgg.TarEndMat(&End, gun.NowBase.Mat, &gun.End.RotXMat, &gun.End.RotYMat, gun.TragetPos, D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	gun.NowAnime = 0.0f;
	gun.AnimeFrame = 0.05f;

	gun.BulletFlg = false;
	gun.GunMoveFlg = true;
	gun.EndFlg = false;

	gun.GunMoveEndFlg = false;

}

bool C_GunMoveBaseE::UpdateGun(void)
{
	C_GunMove *TmpMove;

	TmpMove = GunMove->Action(&gun);
	if (TmpMove != nullptr) {
		delete GunMove;
		GunMove = TmpMove;
	}

	return true;
}

void C_GunMoveBaseE::CountRay(const bool * JudgFlg)
{
	if (*JudgFlg == true) {
		gun.RayCountNow -= 1;
	}
	else {
		gun.RayCountNow += 1;
		if (gun.RayCountNow > gun.RayCountInit)gun.RayCountNow = gun.RayCountInit;
	}
}

void C_GunMoveBaseE::SetGunMatT(const D3DXMATRIX *Mat)
{
	gun.ConnectMat = *Mat;
	gun.NowBase.TraPos = gunEA->GetPos();
	judgg.SetTransMat(&gun.NowBase.Trans, &gun.NowBase.TraPos);
	gun.NowBase.Mat = gun.NowBase.Trans*gun.ConnectMat;

	gun.NowBase.DrawMat = gun.NowBase.RotX*(gun.NowBase.RotY*gun.NowBase.Mat);

	gunEA->Update(gun.NowBase.DrawMat);
}
