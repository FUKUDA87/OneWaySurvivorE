#include "ENo101_GNo1_Stop.h"
#include"ENo101_GNo1_Attack.h"
#include"ENo101_GNo1_NoMove.h"

C_ENo101_GNo1_Stop::C_ENo101_GNo1_Stop()
{
	Count = CountInit = 60 * 2;
}

C_E_GunMoveBase * C_ENo101_GNo1_Stop::Move(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	if (ChangePhase(s_Data, NowPhase) == true)return new C_ENo101_GNo1_NoMove();

	Count--;
	if (Count < 0)Count = 0;
	if (Count <= 0)return new C_ENo101_GNo1_Attack();
	return nullptr;
}
