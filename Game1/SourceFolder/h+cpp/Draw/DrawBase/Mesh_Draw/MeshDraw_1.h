#pragma once
#include"../MeshBase.h"

class C_MeshDraw_1 :public C_MeshBase {
public:
	//�\��
	virtual void Draw(const D3DXMATRIX *Mat)=0;
};