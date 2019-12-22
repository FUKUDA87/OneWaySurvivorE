#pragma once
#include"BulletPA.h"
#include<d3dx9.h>
#include"../../GameSource/InvBi.h"

extern Inv inv;

class BulletEA :public BulletPA {
protected:
public:
	virtual void InitE();
	BulletEA(D3DXMATRIX Mat, D3DXMATRIX GmMat, D3DXVECTOR3 Pos, bool PFlg) :BulletPA(Mat, GmMat, Pos, PFlg) { 
		InitE();
	};
	void Draw3D();
};