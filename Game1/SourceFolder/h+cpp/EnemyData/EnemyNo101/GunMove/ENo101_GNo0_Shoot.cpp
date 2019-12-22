#include "ENo101_GNo0_Shoot.h"
#include"ENo101_GNo0_Stop.h"
#include"ENo101_gNo0_NoMove.h"

C_ENo101_GNo0_Shoot::C_ENo101_GNo0_Shoot()
{
	BulletNum = 1;
	BulletCount = 0;
	BulletInitCount = 0;
	BulletShoot = false;
	InitFlg = true;
}

C_E_GunMoveBase * C_ENo101_GNo0_Shoot::Move(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	if (ChangePhase(s_Data, NowPhase) == true)return new C_ENo101_GNo0_NoMove();

	if ((BulletShoot == true) && (s_Data->BulletFlg == false)) {
		if (BulletNum <= 0)return new C_ENo101_GNo0_Stop();
		InitFlg = true;
	}
	if (InitFlg == true) {
		BulletNum--;
		BulletCount = BulletInitCount;
		BulletShoot = false;
		InitFlg = false;
	}
	if (BulletShoot == true)return nullptr;
	BulletCount--;
	if (BulletCount < 0)BulletCount = 0;
	if (BulletCount <= 0) {
		BulletShoot = true;
		s_Data->BulletFlg = true;
	}
	return nullptr;
}
