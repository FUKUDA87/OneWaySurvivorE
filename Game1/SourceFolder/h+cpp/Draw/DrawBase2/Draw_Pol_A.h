#pragma once
#include"Draw3D_Base2.h"
#include<string>
#include"../../Manager/TextureManager/DrawTextureManager_Base.h"


//�|���S���̕\��
class C_Draw_Pol_BASE_A :public C_Draw3D_Base2 {
public:
	C_Draw_Pol_BASE_A();
	C_Draw_Pol_BASE_A(const D3DXVECTOR3 *Pos_A, const D3DXVECTOR3 *Pos_B, const D3DXVECTOR3 *Pos_C, const D3DXVECTOR3 *Pos_D);
	C_Draw_Pol_BASE_A(std::string FileName, const S_TEX_POS *Pos);
	C_Draw_Pol_BASE_A(std::string FileName, const S_TEX_DRAW_DATA* Data);

	//�\���֐�
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);

	//�ړ��ʂ̃Z�b�g
	void Set_MoveVec(const D3DXVECTOR3 *MoveVec);


	//���b�V���n��
	LPD3DXMESH Get_Mesh(void);

	//�|���S���̒��_�n��
	D3DXVECTOR3 Get_Pol_Pos(const int *PosNo);

	//�\���s��̓n��
	D3DXMATRIX Get_DrawMat(void);

protected:

	/*�����o�[�ϐ�*/
	//�\���̃e�N�X�`��
	TEXTURE M_Tex;
	VERTEX v[4];
	D3DXVECTOR3 v_Pos[4];

	/*�֗������o�[�֐�*/

	//�e�N�X�`���̃��[�h
	void Texture_Load(std::string FileName, const S_TEX_POS *Pos);
	//�e�N�X�`���̃��[�h�ƐF�̍폜
	void Texture_Load(std::string FileName, const S_TEX_DRAW_DATA* Data);
	//�e�N�X�`���̏��n��
	TEXTURE Get_S_Texture(void) {
		return M_Tex;
	}

	//�|���S���̒��_�Z�b�g
	void Pol_SetPos(const D3DXVECTOR3* v_A, const D3DXVECTOR3* v_B, const D3DXVECTOR3* v_C, const D3DXVECTOR3* v_D);

	//�|���S���̓����x�̓���
	void Pol_SetAllColor(const int *Alpha);

	//�e�N�X�`�����W�̑���
	void Pol_SetAllTex(const D3DXVECTOR2* t_A, const D3DXVECTOR2* t_B, const D3DXVECTOR2* t_C, const D3DXVECTOR2* t_D);

	//������
	void Init_Pol(void);


	//�e�N�X�`���Ȃ��̕\��
	void Draw_Pol_No1(void);

	//�e�N�X�`������̕\��
	void Draw_Pol_No2(void);

private:
	
};