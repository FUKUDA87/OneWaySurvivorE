#include "ENo101_GNo1_NoMove.h"
#include"ENo101_GNo1_Attack.h"

C_E_GunMoveBase * C_ENo101_GNo1_NoMove::Move(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	if ((*NowPhase == Phase4) || (*NowPhase == Phase6)) {
		D3DXMatrixRotationX(&s_Data->NowRot.RotXMat, D3DXToRadian(s_Data->Gun.AngX));
		D3DXMatrixRotationY(&s_Data->NowRot.RotYMat, D3DXToRadian(s_Data->Gun.AngY));
		return new C_ENo101_GNo1_Attack();
	}
	return nullptr;
}
