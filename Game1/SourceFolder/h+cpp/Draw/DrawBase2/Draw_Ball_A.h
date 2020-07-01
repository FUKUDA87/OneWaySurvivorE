#pragma once
#include"Draw3D_Base2.h"
#include"../../Draw/3D/Ball/Ball3D.h"
#include<vector>

class C_Draw_Ball_A :public C_Draw3D_Base2 {
public:
	C_Draw_Ball_A(const float Dis);
	~C_Draw_Ball_A();

	//�\���֐�
	void Draw3D(const D3DXVECTOR3 *CameraPos);

	//�ړ��ʂ̃Z�b�g
	void Set_MoveVec(const D3DXVECTOR3 *MoveVec) {

	}

	//���b�V���n��
	LPD3DXMESH Get_Mesh(void);

	//�|���S���̒��_�n��
	D3DXVECTOR3 Get_Pol_Pos(const int *PosNo);

	//�~�̔��a�n��
	float Get_Dis(void);

	//�\���s��̓n��
	D3DXMATRIX Get_DrawMat(void) {
		return M_Mat;
	}
protected:
	float M_Dis;

	std::vector<c_Ball3D*>M_Ball;

	//�S�폜
	void Delete_All_Ball(void);

	int Count;
};