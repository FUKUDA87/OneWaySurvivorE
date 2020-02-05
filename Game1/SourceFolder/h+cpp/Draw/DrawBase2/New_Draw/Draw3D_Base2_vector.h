#pragma once
#include"../Draw3D_Base2.h"
#include<vector>

class C_Draw3D_Base2_vector {
public:
	~C_Draw3D_Base2_vector();

	//�\��
	void Draw(const D3DXVECTOR3 *CameraPos);

	//�X�V
	bool Update(void);

	//�s��̍X�V
	void Set_Mat(const D3DXMATRIX *Mat);

	//�\���̏�����
	void New(C_Draw3D_Base2 * New_Draw3D);

private:
	std::vector<C_Draw3D_Base2 *> M_Draw;

	//�폜
	void Delete(void);
	//�폜
	void Delete_All(void);
};