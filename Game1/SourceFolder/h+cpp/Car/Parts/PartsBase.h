#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../GameSource/CharaBase.h"
#include"../../Draw/DrawBase2/Draw3D_Base2.h"
#include<vector>

class C_PartsBase:public C_CharaBase {
public:
	/*�Ԃ���̋���
	����

	*/
	C_PartsBase();
	~C_PartsBase();

	//�\��
	virtual void Draw_Parts(const D3DXVECTOR3 *CameraPos);
	virtual void Draw_Parts(const D3DXVECTOR3 *CameraPos,const bool *H_Body_DamageFlg);

	//�Ԃ̊g��s��̃Z�b�g
	void Set_ScalPos_Body(const D3DXVECTOR3 *set_Car_ScalPos);
	void Set_ScalPos_Body(const D3DXVECTOR3 *set_Car_ScalPos, const D3DXVECTOR3 *set_Parts_ScalPos);

	//�\���̍s��n��
	virtual D3DXMATRIX Get_Draw_Mat(void);

	//�\���̕\���s��n��
	virtual D3DXMATRIX Get_Draw_DrawMat(void);

	//�\���̕\���T�C�Y�n��
	D3DXVECTOR3 Get_Draw_ScalPos(void);


	//�\�����n��
	BASE3D Get_BASE3D(void) {
		return M_Base3D;
	}

	//�X�s�[�h�Z�b�g
	void SetSpeed(const int *GetNowSpeed, const int *GetMaxSpeed);

	//�\���̃R���X�g���N�^
	void Draw_New(C_Draw3D_Base2* set_Draw);

	//�Ԃ̃T�C�Y�n��
	D3DXVECTOR3 Get_Car_ScalPos(void) {
		return M_Car_ScalPos;
	}

	/*
	���肷��n��
	*/
	//�|���S��Flg
	int Get_Draw_Draw_JudgFlg(void);

	//�|���S���̒��_
	D3DXVECTOR3 Get_Draw_Pol_Pos(const int *PosNo);

	//���b�V��
	LPD3DXMESH Get_Draw_Mesh(void);

	//IdenFlg
	bool Get_Draw_Iden_Flg(void);

	//�\�����a�n��
	float Get_Draw_Dis(void);

protected:
	//�\�����
	BASE3D M_Base3D;

	//�Ԃ̃T�C�Y
	D3DXVECTOR3 M_Car_ScalPos;

	//�\���ϐ�
	C_Draw3D_Base2* M_Draw;

	//�X�s�[�h(�J�[�̍��̃X�s�[�h�ƍő�X�s�[�h)
	S_GAGE Speed;

	//�\���̍폜
	void Draw_AllDelete(void);

	//�\���P
	virtual void Draw_Draw(const D3DXVECTOR3 *CameraPos);
	virtual void Draw_Draw(const D3DXVECTOR3 *CameraPos,const bool *H_Body_DamageFlg);

	void Set_TransPos(const D3DXVECTOR3 *set_Pos);

	//�\���̍s��S����
	void Set_All_Draw_Mat(const D3DXMATRIX *Mat);

	//�\���ɎԂ̃T�C�Y����
	void Set_Body_ScalPos_Draw(void);
	void Set_Body_ScalPos_Draw(const D3DXVECTOR3 *ScalPos);

	//�\���Ɣ�\���̃t���O
	bool Draw_Flg;
private:

};