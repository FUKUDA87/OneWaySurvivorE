#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Damage_Num_Base {
public:
	C_Damage_Num_Base(const D3DXVECTOR3 *Pos_3D,const D3DXMATRIX * Mat,const int *Damage_Num);

	//�X�V
	virtual bool Update(void);

	//�\��
	void Draw_2D(void);

	//�\����3D���W�n��
	D3DXVECTOR3 Get_Pos_3D(const D3DXMATRIX * Mat);

	//�\����2D���W�ɃZ�b�g
	void Set_Pos_2D(const D3DXVECTOR3 *Pos_2D);

protected:
	virtual void Move(void);

	//�\������
	int M_Count;

	//�\���T�C�Y
	float M_ScalSize;

	//�\�����W
	D3DXVECTOR3 M_Pos_2D;

private:

	//�\�����W
	D3DXVECTOR3 M_Vec;

	//�\���̍\����
	s_TEXTURE_DATA M_TEX;

	//�\��Flg
	bool M_Draw_Flg;

	//�_���[�W��
	int M_Damage_Num;
};