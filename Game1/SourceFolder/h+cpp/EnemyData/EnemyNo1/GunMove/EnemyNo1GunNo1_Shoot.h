#pragma once
#include"../../Base&Manager/EnemyGunMoveBase.h"

class C_ENo1_GNo1_Shoot :public C_E_GunMoveBase {
public:
	C_ENo1_GNo1_Shoot();
	C_E_GunMoveBase* Move(S_ENEMYGUNDATA* s_Data, int *NowPhase);
protected:

private:
	int BulletNum,BulletCount,BulletInitCount;
	bool BulletShoot,InitFlg;
};