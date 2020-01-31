#pragma once
#include"PartsBase.h"
#include"../Move/Parts/Move_Parts_Base.h"

class C_Car_Parts_Base :public C_PartsBase {
public:
	C_Car_Parts_Base(const S_CAR_PARTS_DATA *set_Data);
	~C_Car_Parts_Base();

	//�X�V
	bool UpdateParts(const D3DXMATRIX *Mat);
	bool UpdateParts(const D3DXMATRIX *Mat, const int *GetNowSpeed, const int *GetMaxSpeed,const D3DXVECTOR3* Car_ScalPos);

	//�p�[�c���n��
	S_CAR_PARTS_DATA Get_Parts_Data(void) {
		return M_Parts_Data;
	}

	//�����̏�����
	void New_Move(C_Move_Parts_Base *New);

	//�����̃Z�b�g
	void Set_I_MoveFlg(const int Flg);

protected:
	//�Ԃ̈ʒu�f�[�^
	S_CAR_PARTS_DATA M_Parts_Data;

	//�p�[�c�̃f�[�^�쐬
	S_CAR_PARTS_DATA Get_S_PARTS_DATA(const D3DXVECTOR3 TransPos, const D3DXVECTOR3 Ang);

	//�����̍폜
	void Move_Delete(void);

	C_Move_Parts_Base *M_Move;

	//0����~�A�P�������A�Q�����o�[�X
	int M_I_MoveFlg;
private:

};