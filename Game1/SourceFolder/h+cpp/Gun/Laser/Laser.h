#pragma once
#include<d3dx9.h>
#include"LaserBase.h"
#include"../../GameSource/InvBi.h"

extern Inv inv;

class LaserA:public LaserBase{
protected:
	D3DXVECTOR3 vec;
public:
	void Init();
	LaserA() {
		Init();
	}
	LaserA(float Dis):LaserBase(Dis) {
		Init();
	}
	D3DXVECTOR3 GetLasVec();
	bool UpdateS(D3DXMATRIX Mat, D3DXMATRIX tmp);
	bool UpdateL(float Dis, bool Flg);
	void Draw3D();
};