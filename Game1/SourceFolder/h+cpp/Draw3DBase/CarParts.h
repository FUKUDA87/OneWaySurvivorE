#pragma once
#include"PartsBase.h"
#include<vector>
#include"BaseDataManager/CarDataManager.h"
#include"../GameSource/Judgment.h"
#include"Car_Parts_Data.h"
#include"Car_Parts_Joint.h"
#include"../Const/Const_PartsTypeNo.h"
#include"../GameSource/StructClass/Parts_Set_Data.h"
#include"Car_Parts_Size.h"

class C_CarParts:public C_Car_Parts_Size {
public:
	C_CarParts();
	~C_CarParts();

	//�p�[�c�̕\��
	void Draw_Car_Parts(const D3DXVECTOR3* CameraPos);
	//�p�[�c�̍X�V
	bool Update_Car_Parts(void);
	//�p�[�c�̏��n��

	//�p�[�c�̍폜
	void Delete_Parts(unsigned int *PartsNo);

	//�p�[�c�Ƀ_���[�W

	//�J�����ɍs��n��
	D3DXMATRIX Get_Camera_Mat(void);

	//�p�[�c���n��
	unsigned int Get_Car_Parts_Num(void) {
		return M_Car_Parts.size();
	}

	/*
	����
	*/

	//�\����Flg
	int Get_Parts_Draw_Draw_JudgFlg(const unsigned int *M_Car_PartsNo);

	//�|���S���̒��_
	D3DXVECTOR3 Get_Parts_Draw_Pol_Pos(const unsigned int *M_Car_PartsNo,const int *PosNo);

	//���b�V��
	LPD3DXMESH Get_Parts_Draw_Mesh(const unsigned int *M_Car_PartsNo);

	//IdenFlg
	bool Get_Parts_Draw_Iden_Flg(const unsigned int *M_Car_PartsNo);

	//�\���s��n��
	D3DXMATRIX Get_Parts_Draw_DrawMat(const unsigned int *M_Car_PartsNo);

	//�p�[�c��Hp�����炷����
	bool Damage_CarParts(const unsigned int *M_CarPartsNo, const int *Damage);

	//�\���s��n��
	float Get_Parts_Draw_Dis(const unsigned int *M_Car_PartsNo);

	BODYDATA Get_BODYDATA(void) {
		return BodyData;
	}

	/*�p�[�c�̃T�E���h�f�[�^�̎擾*/

protected:
	//�p�[�c�\���ϐ�
	std::vector<C_Car_Parts_Joint*>M_Car_Parts;

	//�Ԃ̃f�[�^
	BODYDATA BodyData;
	//�Ԃ̃p�[�c���㏑��Flg
	bool M_Parts_Save_Flg;

	//�p�[�c�̏�����
	virtual void New_Set_Car_Parts(const BODYDATA *CarData);
	virtual void New_Set_Car_Parts(const int *CarNo,std::vector<C_Parts_Set_Data*>M_Set_Data);

	//�p�[�c�̑S�폜
	void Delete_ALL_Parts(void);

	//�p�[�c�̏�����(�v���C���[)
	void New_CarParts(const BODYDATA *CarData);
	void New_CarParts(std::vector<C_Parts_Set_Data*>M_Set_Data);
	S_CAR_PARTS_DATA* Get_Data_CarParts(const int *TypeNo,const int JointNo);
	//�p�[�c�̏�����(�G�l�~�[)

	//�Ԃ̃p�[�c�̏�����
	void New_Car_Parts_Data(const int *CarNo);

	//�Ԃ̓����蔻��p�̏��̏�����
	virtual void New_Car_Judg_Parts(void);
private:

};