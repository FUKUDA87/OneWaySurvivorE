#include "Enemy_Gun_Move_Base.h"

C_GunMoveBase_A * C_Enemy_Gun_Move_Base::Update(S_GUN_DATA * s_Data, S_GUN_UPDATE_DATA * s_Update)
{
	return nullptr;
}

D3DXMATRIX C_Enemy_Gun_Move_Base::Get_Mat(const QUAMAT * Rot, const D3DXMATRIX * StandMat)
{
	D3DXMATRIX Mat;

	Mat = Rot->RotXMat*(Rot->RotYMat*(*StandMat));

	return Mat;
}

C_GunMoveBase_A * C_Enemy_Gun_Move_Base::Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX * StandMat, C_GunMoveBase_A * Move)
{
	End_Move(s_Data);

	s_Data->DrawBase.Mat=Get_Mat(&s_Data->NowRot, StandMat);
	return Move;
}

C_GunMoveBase_A * C_Enemy_Gun_Move_Base::Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX * StandMat)
{
	s_Data->DrawBase.Mat = Get_Mat(&s_Data->NowRot, StandMat);
	return nullptr;
}

void C_Enemy_Gun_Move_Base::End_Move(S_GUN_DATA * s_Data)
{
}
