#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"
#include"../../../Draw/DrawBase2/Draw3D_Base2.h"
#include<vector>
#include"../../../GameSource/Count.h"

class C_Bullet_Base{
public:
	//�e�̔ԍ��Əe���̍s��
	C_Bullet_Base(const D3DXMATRIX *Mat);
	//�v���C���[���Ə������킹�����̃R���X�g���N�^
	C_Bullet_Base(const D3DXMATRIX *Mat, const S_RAY_HIT_JUDG_DATA* RayData);
	~C_Bullet_Base();

	//�\��
	virtual void Draw(const D3DXVECTOR3 *CameraPos);

	//���C�҂̈ړ�Vec���Z
	virtual void MoveVec(const D3DXVECTOR3 *MoveVec);

	//�\���̓n��
	S_BULLET Get_S_BULLET(void) {
		return M_S_Bullet;
	}

	//�e�̏��̎擾
	void Set_S_BULLET(const int *BulletTypeNo);

	//�\���̍\���̓n��
	BASE3D Get_BASE3D(void) {
		return M_Base;
	}

	//�\���̍\���̂̑��
	void Set_BASE3D(const BASE3D *s_Base) {
		M_Base = *s_Base;
	}

	//�s�����
	void Set_Mat(const D3DXMATRIX *Mat);

	//�O�i
	bool Move(void);

	//�n�ʂƕǂ̔���n��
	bool Get_GroWal_Judg_Flg(void) {
		return M_GroWal_Judg_Flg;
	}

	//�n�ʂƕǂ̔���̓���
	void Set_GroWal_Jufg_Flg(const bool *Flg) {
		M_GroWal_Judg_Flg = *Flg;
	}
protected:
	//�J�E���g�_�E���̍폜
	void Delete_Count(void);

	/*�ϐ�*/
	S_BULLET M_S_Bullet;

	//�\���N���X
	std::vector<C_Draw3D_Base2*>M_Draw;
	//�ړ��s��
	BASE3D M_Base;

	/*�e�̏������Ɏg�p*/
	S_PolMat_INIT Get_Init_S_PolMat_INIT(const D3DXMATRIX *Mat, const int TexNo, const int PolNum, const float PolSize);

	S_TEX_POS Get_Tex_Pos(const int W, const int H);
private:

	void Init_S_Bullet(void);

	//�n�ʂƕǂ𔻒肷��Flg
	bool M_GroWal_Judg_Flg;

	//�\���̑S�폜
	void M_Draw_Delete_All(void);

	//�e���Ə��̕����ɌX���鏈��
	void RayPos_Bullet(const S_RAY_HIT_JUDG_DATA* RayData);

	//������
	void Init(void);

	C_Count *M_Count;
};