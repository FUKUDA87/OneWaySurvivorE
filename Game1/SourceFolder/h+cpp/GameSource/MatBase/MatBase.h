#pragma once
#include<d3dx9.h>

class C_MatBase {
public:
	//��]X�s��쐬
	D3DXMATRIX Set_RotXMat(const float *Ang);

	//��]X�s��쐬
	D3DXMATRIX Set_RotYMat(const float *Ang);

	//��]X�s��쐬
	D3DXMATRIX Set_RotZMat(const float *Ang);

	//�ʒu�̍s��쐬
	D3DXMATRIX Set_TransMat(const D3DXVECTOR3 *Pos);

	//�g��k���̍s��쐬
	D3DXMATRIX Set_ScalMat(const D3DXVECTOR3 *Pos);

	//�s��̏�����
	D3DXMATRIX Init_Mat(void);

protected:

private:
	
};