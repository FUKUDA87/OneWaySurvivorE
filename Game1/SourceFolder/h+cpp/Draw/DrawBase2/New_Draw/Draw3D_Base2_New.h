#pragma once
#include"../Draw3D_Base2.h"
#include<string>

class C_Draw3D_Base2_New {
public:
	C_Draw3D_Base2_New(C_Draw3D_Base2 * New_Draw3D);
	~C_Draw3D_Base2_New();

	//�\��
	void Draw(const D3DXVECTOR3 *CameraPos);

	//�X�V
	bool Update(void);

	//�s��̍X�V
	void Set_Mat(const D3DXMATRIX *Mat);

	//�\���̏�����
	void New(C_Draw3D_Base2 * New_Draw3D);

private:
	C_Draw3D_Base2 * M_Draw;

	//�폜
	void Delete(void);
};