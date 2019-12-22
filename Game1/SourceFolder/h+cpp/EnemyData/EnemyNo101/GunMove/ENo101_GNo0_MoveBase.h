#pragma once
#include"../../Base&Manager/EnemyGunMoveBase.h"

class C_ENo101_GNo0_MoveBase :public C_E_GunMoveBase {
public:
	C_ENo101_GNo0_MoveBase();
	virtual C_E_GunMoveBase* Move(S_ENEMYGUNDATA* s_Data, int *NowPhase);
	bool ChangePhase(S_ENEMYGUNDATA* s_Data, int *NowPhase);
protected:

private:
	int Count, CountInit;
};