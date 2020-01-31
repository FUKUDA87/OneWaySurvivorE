#pragma once
#include"../../Gun/GunDraw/GunMove/GunMoveBase_A.h"
#include"../../GameSource/Struct.h"

class C_Enemy_Gun_Move_Base :public C_GunMoveBase_A {
public:
	C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, S_GUN_UPDATE_DATA* s_Update);
protected:
	//�\���̍s��쐬
	D3DXMATRIX Get_Mat(const QUAMAT *Rot, const D3DXMATRIX *StandMat);

	//���̓����n��
	C_GunMoveBase_A* Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX *StandMat, C_GunMoveBase_A * Move);
	C_GunMoveBase_A* Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX *StandMat);

	//�I������
	virtual void End_Move(S_GUN_DATA *s_Data);

	
};