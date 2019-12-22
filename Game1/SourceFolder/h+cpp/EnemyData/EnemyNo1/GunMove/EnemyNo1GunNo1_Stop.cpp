#include "EnemyNo1GunNo1_Stop.h"
#include"EnemyNo1GunNo1_Attack.h"

C_ENo1_GNo1_Stop::C_ENo1_GNo1_Stop()
{
	Count = CountInit = 60*3;
}

C_E_GunMoveBase * C_ENo1_GNo1_Stop::Move(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	Count--;
	if (Count < 0)Count = 0;
	if (Count <= 0)return new C_ENo1_GNo1_Attack();
	return nullptr;
}
