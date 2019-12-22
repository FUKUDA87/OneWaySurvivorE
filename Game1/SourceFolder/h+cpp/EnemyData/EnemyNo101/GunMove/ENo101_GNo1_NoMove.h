#pragma once
#include"ENo101_GNo1_MoveBase.h"

class C_ENo101_GNo1_NoMove :public C_ENo101_GNo1_MoveBase {
public:
	C_E_GunMoveBase* Move(S_ENEMYGUNDATA* s_Data, int *NowPhase);
protected:

private:

};