#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"
#include"../../../Draw/DrawBase2/Draw3D_Base2.h"

class C_BulletData_Base {
public:
	//弾の情報を入手
	virtual S_BULLET_DATA Get_Data(void) = 0;
	//弾の表示数渡し
	virtual int Get_DrawNum(void)=0;
	//弾の表示コンストラクタ渡し
	virtual C_Draw3D_Base2* Get_Draw(const int *BulletDrawNo,const D3DXMATRIX *Mat)=0;



protected:
	S_PolMat_INIT Get_Init_S_PolMat_INIT(const D3DXMATRIX *Mat, const int TexNo, const int PolNum, const float PolSize);

	S_TEX_POS Get_Tex_Pos(const int W, const int H);
private:

};