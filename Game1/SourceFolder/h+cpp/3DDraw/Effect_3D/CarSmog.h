#pragma once
#include"Smog.h"
#include<vector>

class C_SmokeCar {
public:
	C_SmokeCar();
	~C_SmokeCar();
	//�A�b�v�f�[�g
	bool Update_CS(const CHARABASE* CharaBase, const int *CarNo, const D3DXMATRIX *CarMat, const D3DXVECTOR3* CarMoveVec);
	//�\��
	void Draw3D_CS(const D3DXVECTOR3 *CamPos);
private:
	//���N���X
	std::vector<C_Smog*>M_C_Smoke;

	/*�֐�*/

	//���S�č폜
	void AllDelete_Smoke(void);
};