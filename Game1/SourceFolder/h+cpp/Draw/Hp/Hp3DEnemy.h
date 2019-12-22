#pragma once
#include"HpBase.h"

class C_Hp3D :public C_HpBase {
public:
	//ÇòÅFïùÅAÇôÅFçÇÇ≥
	C_Hp3D(const D3DXVECTOR2 *TransPos);
	void Draw2DAll(const int *NowHp, const int *MaxHp) {};
	void Draw3DAll(const int *NowHp, const int *MaxHp, const D3DXVECTOR3 *CamPos, const D3DXMATRIX *Mat,const float UpY);
protected:
	VERTEX v[4];
	TEXTURE m_PolTex;
	void Init(void);
private:

};