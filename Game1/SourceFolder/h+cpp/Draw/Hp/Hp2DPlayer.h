#pragma once
#include"HpBase.h"

class C_Hp2D:public C_HpBase {
public:
	C_Hp2D(const D3DXVECTOR3 *ScalPos, const D3DXVECTOR3 *TransPos);
	virtual void Draw2DAll(const int *NowHp, const int *MaxHp);

	virtual void Draw3DAll(const int *NowHp, const int *MaxHp, const D3DXVECTOR3 *CamPos, const D3DXMATRIX *Mat, const float UpY) {};
protected:
	void Draw2D(void);
	void Init(void);

	int TexNum;
	TEXTURE m_HpTex[2];

private:
	
};