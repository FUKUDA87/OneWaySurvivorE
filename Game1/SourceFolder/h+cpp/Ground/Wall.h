#pragma once
#include<d3dx9.h>
#include"ground.h"
#include"../GameSource/Struct.h"
#include<vector>

const int WNum = 2;
class Wall :public C_Ground {
public:
	Wall(const int *i);
	Wall(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4, const S_GROUND_INIT_DATA * Init_Data_Ground);

	//�ǂ̐�
	int Get_Wall_Num(void) {
		return 2;
	}

	void SuperDraw();

	//�ǂ̃R���W�������f���n��
	LPD3DXMESH GetColModWall(void) {
		return M_Wall.ColModMesh.lpMesh;
	}
	//��3D�̕\���s��n��
	D3DXMATRIX Get_DrawMat_Wall(const int *Wall_Num);
	//��3D�̍s��n��
	D3DXMATRIX Get_Mat_Wall(const int *Wall_Num);

	//�ǂ̏��n��
	S_Base3D_2 Get_Data_Wall(const int *Wall_Num);

	//�\���̕ύX
	void Set_Draw_Flg_Wall(const int *Wall_Num, const bool *DrawFlg);

protected:

	void WaDraw();

private:
	//��3D�p
	S_Object3D_Data M_Wall;

	S_Base3D_2 Wall3D[2];

	//�ǂ̃T�C�Y�̏�������̏�����
	void Init_Wall3D_All(void);

	//�ǂ̏�����
	void Init_Wall();

	//�n�ʂ̍s�񂪒P�ʍs�񂶂�Ȃ��ꍇ�̏�����
	void Init_Wall_Mat(void);

	//�n�ʂ̕\���s��ɒP�ʍs�񂪎g�p����Ă���ꍇ�̏�����
	void Init_Wall_Iden(void);

	//�ǂ̃T�C�Y�̏�����
	void Init_Wall_SizeZ(const D3DXVECTOR3 * Ground_Vec, const int *Wall_No);
};