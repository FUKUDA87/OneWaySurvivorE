#pragma once
#include"HpbarBase.h"

class C_Hpbar2D:public C_HpbarBase {
public:
	C_Hpbar2D();

	// 2D�\��
	virtual void Draw2D(const int *NowHp, const int *MaxHp);
protected:
	s_TEXTURE_DATA hpTex[2];
	D3DXVECTOR2 Pos,ScalPos;

	void DrawA(const int *NowHp, const int *MaxHp);
};