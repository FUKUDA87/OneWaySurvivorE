#pragma once
#include<d3dx9.h>
#include"MuzFlaBase.h"

class MuzFlaPA :public MuzFlaBase{
protected:
public:
	void Init();
	MuzFlaPA() { Init(); };
	MuzFlaPA(D3DXMATRIX Mat,D3DXMATRIX Tmp);
	~MuzFlaPA() {};
	void Draw3D();
	bool Update();
};