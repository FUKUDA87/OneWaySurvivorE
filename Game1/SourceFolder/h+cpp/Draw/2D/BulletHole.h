#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../GameSource/Judgment.h"

class C_BulletHole {
public:
	C_BulletHole(const D3DXVECTOR3 *Pos,const float *AngZ,const D3DXVECTOR3 *ScalPos);
	C_BulletHole(const D3DXVECTOR3 *Pos, const float *AngZ, const D3DXVECTOR3 *ScalPos,int No);
	~C_BulletHole();
	//初期化
	void InitBulHol(void);
	void InitBulHol(int No);
	//表示
	void Draw2DBH(void);
	//表示の行列作成
	D3DXMATRIX GetDrawMatBulHol(void);
protected:
	Judg judg;
private:
	CHARA2D BulHol;
};