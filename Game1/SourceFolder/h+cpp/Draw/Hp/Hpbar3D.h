#pragma once
#include"HpbarBase.h"

class C_Hpbar3D :public C_HpbarBase {
public:
	C_Hpbar3D();

	// 3D表示
	void Draw3D(const int *NowHp, const int *MaxHp
		, const D3DXMATRIX *Mat, const D3DXVECTOR3 *CamPos
		, const D3DXVECTOR3 *CharaScalPos);
protected:
	VERTEX v[4];
	LPDIRECT3DTEXTURE9 hpTex;

	D3DXVECTOR2 ScalPos;
	float yUp;

	bool drawFlg;

	// 初期化
	void Init(void);

};