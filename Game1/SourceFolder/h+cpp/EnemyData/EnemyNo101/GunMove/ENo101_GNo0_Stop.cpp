#include "ENo101_GNo0_Stop.h"
#include"ENo101_GNo0_Attack.h"
#include"ENo101_gNo0_NoMove.h"

C_ENo101_GNo0_Stop::C_ENo101_GNo0_Stop()
{
	Count = CountInit = 60 * 1;
}

C_E_GunMoveBase * C_ENo101_GNo0_Stop::Move(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	if (ChangePhase(s_Data, NowPhase) == true)return new C_ENo101_GNo0_NoMove();

	Count--;
	if (Count < 0)Count = 0;
	if (Count <= 0)return new C_ENo101_GNo0_Attack();
	return nullptr;
}
