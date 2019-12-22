#pragma once
#include<d3dx9.h>
#include"BulletBase.h"

class BulletPA :public BulletBase{
protected:
public:
	void Init();
	BulletPA();
	BulletPA(D3DXMATRIX Mat,D3DXMATRIX GmMat, D3DXVECTOR3 Pos, bool PFlg);
	~BulletPA();
	void Draw3D();
	bool Update();
	bool UpdateMove(D3DXVECTOR3 bVec);
};