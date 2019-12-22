#include "ENo101_gNo0_NoMove.h"
#include"ENo101_GNo0_Attack.h"

C_E_GunMoveBase * C_ENo101_GNo0_NoMove::Move(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	if ((*NowPhase == Phase3) || (*NowPhase == Phase5)) {
		s_Data->Hp.NowHp = s_Data->Hp.MaxHp;
		D3DXMatrixRotationX(&s_Data->NowRot.RotXMat, D3DXToRadian(s_Data->Gun.AngX));
		D3DXMatrixRotationY(&s_Data->NowRot.RotYMat, D3DXToRadian(s_Data->Gun.AngY));
		return new C_ENo101_GNo0_Attack();
	}
	return nullptr;
}
