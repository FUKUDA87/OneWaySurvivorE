#include "Enemy_Gun_Move_Base.h"

C_Enemy_Gun_Move_Base::C_Enemy_Gun_Move_Base()
{
	M_GunInitFlg = true;
}

C_GunMoveBase_A * C_Enemy_Gun_Move_Base::Update(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA * s_Update, CHARABASE * Chara)
{
	return nullptr;
}

void C_Enemy_Gun_Move_Base::Get_Mat(D3DXMATRIX * Mat, const QUAMAT * Rot, const D3DXMATRIX * StandMat)
{
	*Mat = Rot->RotXMat*(Rot->RotYMat*(*StandMat));
}

C_GunMoveBase_A * C_Enemy_Gun_Move_Base::Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX * StandMat, const int * NowHp, C_GunMoveBase_A * Move)
{
	//�e�̉�]�̏�����
	Init_Gun_RotMat(s_Data,NowHp);

	//����̓����̏I������
	if (Move != nullptr) End_Move(s_Data);

	//�\���s��̍���
	Get_Mat(&s_Data->DrawBase.Mat, &s_Data->NowRot, StandMat);

	return Move;
}

C_GunMoveBase_A * C_Enemy_Gun_Move_Base::Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX * StandMat, const int * NowHp)
{
	return Get_Move(s_Data, StandMat,NowHp, nullptr);
}

void C_Enemy_Gun_Move_Base::End_Move(S_GUN_DATA * s_Data)
{
}

bool C_Enemy_Gun_Move_Base::GunStop_Flg(const S_GUN_UPDATE_DATA * s_Update, const CHARABASE * Chara)
{
	if (s_Update->Gun_Stop_Flg == true)return true;

	if (Chara->NowHp <= 0)return true;

	return false;
}

void C_Enemy_Gun_Move_Base::Init_Gun_RotMat(S_GUN_DATA * s_Data, const int * NowHp)
{
	if (NowHp > 0) {
		if (M_GunInitFlg == true)return;

		//��]������Flg��HP�������Ԃ�\��true�ɂ���
		M_GunInitFlg = true;

		return;
	}

	if (M_GunInitFlg != true)return;

	//��]�̏�����
	D3DXMatrixRotationX(&s_Data->NowRot.RotXMat, D3DXToRadian(0.0f));
	D3DXMatrixRotationY(&s_Data->NowRot.RotYMat, D3DXToRadian(0.0f));

	//��]������Flg��HP���[���ł����Ԃ�\��false�ɂ���
	M_GunInitFlg = false;
}

