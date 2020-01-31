#pragma once
#include<d3dx9.h>
#include"../TextureBase.h"

class C_PolygonBase:public C_TextureBase {
public:

protected:
	VERTEX v[4];

	/*�֐�*/

	//�|���S���̒��_�Z�b�g
	void Pol_SetPos(const D3DXVECTOR3* v_A, const D3DXVECTOR3* v_B, const D3DXVECTOR3* v_C, const D3DXVECTOR3* v_D);

	//�|���S���̓����x�̓���
	void Pol_SetAllColor(const int *Alpha);

	//�e�N�X�`�����W�̑���
	void Pol_SetAllTex(const D3DXVECTOR2* t_A, const D3DXVECTOR2* t_B, const D3DXVECTOR2* t_C, const D3DXVECTOR2* t_D);

private:
	
};