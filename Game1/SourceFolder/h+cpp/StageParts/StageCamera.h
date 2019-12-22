#pragma once
#include"../Player/Camera.h"
#include<d3dx9.h>
#include"../GameSource/Judgment.h"

extern Judg judg;

class StageCam :public Camera {
protected:
	float sizeZ,upY;
public:
	StageCam();
	~StageCam() {};
	bool Update(D3DXMATRIX mat, D3DXMATRIX tmp, bool MouFlg);
};