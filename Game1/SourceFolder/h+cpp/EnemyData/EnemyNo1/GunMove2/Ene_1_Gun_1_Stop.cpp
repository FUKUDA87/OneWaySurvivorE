#include "Ene_1_Gun_1_Stop.h"
#include"Enemy_No1_Gun1_Re.h"

C_GunMoveBase_A * C_Ene_1_Gun_1_Stop::Update(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA * s_Update, CHARABASE * Chara)
{
	if (Chara->NowHp > 0) {
		D3DXMatrixRotationX(&s_Data->NowRot.RotXMat, D3DXToRadian(0.0f));
		D3DXMatrixRotationY(&s_Data->NowRot.RotYMat, D3DXToRadian(0.0f));
		return Get_Move(s_Data, &s_Update->StandMat, new C_Enemy_No1_Gun_1_Re());
	}

	return Get_Move(s_Data, &s_Update->StandMat);
}
