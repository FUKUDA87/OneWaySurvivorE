#pragma once
#include<d3dx9.h>
#include"Enemy.h"
#include"../GameSource/Const.h"

class Tire2 :public Enemy {
public:
	Tire2();
	Tire2(D3DXMATRIX GroundMat, float *TransX);
	~Tire2();
	bool TiUpdate();
	bool UpdateTiM();
	void TiDraw();
protected:
	D3DXMATRIX tire2Mat[TNUM];
	D3DXMATRIX tire2TransMat[TNUM], tire2RotMatY[TNUM], tire2RotMatX[TNUM];
private:
	XFILE tire2Mesh;
	float radX;
};