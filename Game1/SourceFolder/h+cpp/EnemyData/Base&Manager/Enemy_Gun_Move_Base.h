#pragma once
#include"../../Gun/GunDraw/GunMove/GunMoveBase_A.h"
#include"../../GameSource/Struct.h"

class C_Enemy_Gun_Move_Base :public C_GunMoveBase_A {
public:
	C_Enemy_Gun_Move_Base();

	//�e�̍X�V
	C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update, CHARABASE *Chara);
protected:
	//�\���̍s��쐬
	void Get_Mat(D3DXMATRIX *Mat, const QUAMAT *Rot, const D3DXMATRIX *StandMat);

	//���̓����n��
	C_GunMoveBase_A* Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX *StandMat, const int *NowHp, C_GunMoveBase_A * Move);
	C_GunMoveBase_A* Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX *StandMat,const int *NowHp);

	//�I������
	virtual void End_Move(S_GUN_DATA *s_Data);

	//�e�̒�~�m�F
	bool GunStop_Flg(const S_GUN_UPDATE_DATA* s_Update, const CHARABASE *Chara);

private:
	//�O��̍X�V�ŏe��HP���[������Flg
	bool M_GunInitFlg;

	//�e�̉�]�̏�����
	void Init_Gun_RotMat(S_GUN_DATA * s_Data, const int *NowHp);
};