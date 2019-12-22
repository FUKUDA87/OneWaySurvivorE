#pragma once
#include<d3dx9.h>

class Inv {
public:
	D3DXMATRIX Inv;
	D3DXVECTOR3 caPos;
	//ビルボード
	bool GetInvRotateMat(D3DXVECTOR3 camPos, D3DXVECTOR3 camLook, D3DXVECTOR3 camHead);
	D3DXMATRIX GetInv() {
		return Inv;
	}
	D3DXVECTOR3 GetcaPos() {
		return caPos;
	}
};