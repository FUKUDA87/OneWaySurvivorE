#pragma once
#include<d3dx9.h>
#include<string>
#include"../../../GameSource/Struct.h"

class c_Num2DBase {
public:
	c_Num2DBase() {};
	c_Num2DBase(int TexNo);
	// •\Ž¦
	void Draw(const int *Num, const D3DXVECTOR2 *Pos
		, const D3DXVECTOR2 *TransVec, const D3DXVECTOR2 *ScalPos
		, const bool *RevFlg);
	void Draw(const int *Num, const D3DXVECTOR2 *Pos
		, const float *ScalSize, const bool *RevFlg);
protected:
	s_TEXTURE_DATA NumTex;
};