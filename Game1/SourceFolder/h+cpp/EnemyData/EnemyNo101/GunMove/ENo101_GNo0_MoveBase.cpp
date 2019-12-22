#include "ENo101_GNo0_MoveBase.h"

C_ENo101_GNo0_MoveBase::C_ENo101_GNo0_MoveBase()
{
}

C_E_GunMoveBase * C_ENo101_GNo0_MoveBase::Move(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	return nullptr;
}

bool C_ENo101_GNo0_MoveBase::ChangePhase(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	if (s_Data->Hp.NowHp <= 0) {
		if (*NowPhase == Phase1)*NowPhase = Phase2;
		if (*NowPhase == Phase3)*NowPhase = Phase4;
		if (*NowPhase == Phase5)*NowPhase = Phase6;
		return true;
	}
	return false;
}
