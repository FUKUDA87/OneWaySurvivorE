#include "ENo101_GNo1_MoveBase.h"

C_ENo101_GNo1_MoveBase::C_ENo101_GNo1_MoveBase()
{

}

C_E_GunMoveBase * C_ENo101_GNo1_MoveBase::Move(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	return nullptr;
}

bool C_ENo101_GNo1_MoveBase::ChangePhase(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	if ((*NowPhase != Phase2)&&(*NowPhase != Phase4) && (*NowPhase != Phase6)) {
		return true;
	}
	return false;
}
