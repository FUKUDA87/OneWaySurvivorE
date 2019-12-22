#pragma once
#include"ENo101_GNo0_MoveBase.h"

class C_ENo101_GNo0_Shoot :public C_ENo101_GNo0_MoveBase {
public:
	C_ENo101_GNo0_Shoot();
	C_E_GunMoveBase* Move(S_ENEMYGUNDATA* s_Data, int *NowPhase);
protected:

private:
	int BulletNum, BulletCount, BulletInitCount;
	bool BulletShoot, InitFlg;
};