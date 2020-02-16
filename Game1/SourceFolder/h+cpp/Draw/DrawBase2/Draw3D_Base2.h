#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../Const/Const_Draw_Judg.h"

class C_Draw3D_Base2 {
public:
	C_Draw3D_Base2();

	//�\���֐�
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos)=0;
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos,bool *Body_DamageFlg);

	//�ړ��ʂ̃Z�b�g
	virtual void Set_MoveVec(const D3DXVECTOR3 *MoveVec) = 0;

	//�X�V����
	virtual bool Update(void);

	//�g��Ək���̒���(�|���Z)
	void Set_ScalPos_Update(const D3DXVECTOR3 *set_ScalPos);

	//�s��n��
	D3DXMATRIX Get_Mat(void) {
		return M_Mat;
	}

	//�s��̃Z�b�g
	virtual void Set_Mat(const D3DXMATRIX*Mat) {
		M_Mat = *Mat;
	}

	//�g��Ək���̓n��
	D3DXVECTOR3 Get_ScalPos(void) {
		return M_ScalPos;
	}

	//�\���s��̓n��
	virtual D3DXMATRIX Get_DrawMat(void);

	//���b�V���̔���n��
	int Get_Draw_JudgFlg(void) {
		return Draw_JudgFlg;
	}

	//���b�V���n��
	virtual LPD3DXMESH Get_Mesh(void)=0;
	
	//�|���S���̒��_�n��
	virtual D3DXVECTOR3 Get_Pol_Pos(const int *PosNo) = 0;

	//�S�̂̃T�C�Y�n��
	D3DXVECTOR3 Get_ScalPos_Body(void) {
		return M_ScalPos_Body;
	}

	bool Get_IdenFlg(void) {
		return IdenFlg;
	}

	//�~�̔��a�n��
	virtual float Get_Dis(void) {
		return 0.0f;
	}

protected:
	//�\���p�s��
	D3DXMATRIX M_Mat;
	D3DXVECTOR3 M_ScalPos,M_ScalPos_Init,M_ScalPos_Body;//_Init�͏��������̕ω��p�ϐ�_Body�͑S�̂̊g��s��

	//MoveVec�𑫂����ɍŏ����������Ȃ�Flg
	bool MoveVecFlg;

	//�\���ɃA�C�f���e�B�e�B���g�p���Ă��邩
	bool IdenFlg;

	/*�����o�[�֐�*/

	//MoveVecFlg�̔���
	bool Get_MoveVecFlg(void);

	//�s��̑��(1)
	void Base_Set_Mat_No1(const D3DXMATRIX *Mat) {
		M_Mat = *Mat;
	}

	//�P�ʍs��̍쐬
	D3DXMATRIX Get_IdenMat(void);

	//
	void Base_Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	//�g��Ək���̒���
	void Set_ScalPos_Init(const D3DXVECTOR3 *set_ScalPos);

	int Draw_JudgFlg;//���蕨�̊m�F�p

	//�T�C�Y�̍쐬
	D3DXVECTOR3 Get_SizeVec(const float *Size);

private:
	//������
	void Init(void);
};