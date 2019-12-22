#pragma once
#include"Num2DBase.h"

class C_Num2DA :public C_Num2DBase {
public:
	C_Num2DA(const D3DXVECTOR3 * Pos, const D3DXVECTOR3 * Scal);
	void Draw2DNB(const int *TmpNum);
protected:

private:

};