#include "EnemyNo1GunNo1_Shoot.h"
#include"EnemyNo1GunNo1_Stop.h"

C_ENo1_GNo1_Shoot::C_ENo1_GNo1_Shoot()
{
	BulletNum = 1;
	BulletCount = 0;
	BulletInitCount = 0;
	BulletShoot = false;
	InitFlg = true;
}

C_E_GunMoveBase * C_ENo1_GNo1_Shoot::Move(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	if ((BulletShoot == true) && (s_Data->BulletFlg == false)) {
		if (BulletNum <= 0)return new C_ENo1_GNo1_Stop();
		InitFlg = true;
	}
	if (InitFlg == true) {
		BulletNum--;
		BulletCount = BulletInitCount;
		BulletShoot = false;
		InitFlg = false;
	}
	if(BulletShoot==true)return nullptr;
	BulletCount--;
	if (BulletCount < 0)BulletCount = 0;
	if (BulletCount <= 0) {
		BulletShoot = true;
		s_Data->BulletFlg = true;
	}
	return nullptr;
}
