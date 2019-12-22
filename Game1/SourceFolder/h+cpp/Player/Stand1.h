#pragma once
#include<d3dx9.h>
#include"tire.h"

class Stand1 :public C_Tire {
private:
	XFILE standMesh;
	float x, y, z;
protected:
	D3DXMATRIX standMat;
public:
	Stand1();
	~Stand1();
	virtual bool SUpdate();
	void SDraw();
};
