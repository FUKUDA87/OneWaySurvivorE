#pragma once
#include<d3dx9.h>
#include<vector>
#include"Damage_Num_Base.h"

class c_DamageNumDraw3DManager
{
public:
	~c_DamageNumDraw3DManager();

	// �X�V����
	bool Update(void);

	// �\��
	void Draw2D(void);

	// 3D�ʒu��2D�ʒu�ɕϊ�
	void UpdatePos2D(const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport, const D3DXMATRIX *PlayerJudgMat);

	// �V�K�쐬
	void NewDamageNumDraw(const int * Character_Type, const D3DXMATRIX * Ray_Mat, const D3DXVECTOR3 * Ray_Vec
		, const float * Ray_Dis, const int * Damage, const bool * DamageFlg, const D3DXMATRIX *PlayerJudgMat);
private:
	std::vector<C_Damage_Num_Base*>damageNumDraw;
};