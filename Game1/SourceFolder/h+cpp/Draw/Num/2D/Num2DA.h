#pragma once
#include"Num2DBase.h"

class C_Num2DA :public c_Num2DBase {
public:
	C_Num2DA(const D3DXVECTOR3 * Pos, const D3DXVECTOR3 * Scal);
	void Draw2D(const int *TmpNum);
protected:

private:
	D3DXVECTOR3 pos, scalPos;
};