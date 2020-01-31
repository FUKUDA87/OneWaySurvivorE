#pragma once
#include"../Bullet_Data_Base/BulletData_Base.h"

class C_BullteData_No1 :public C_BulletData_Base {
public:
	//弾の情報を入手
	S_BULLET_DATA Get_Data(void);
	//弾の表示数渡し
	int Get_DrawNum(void);
	//弾の表示コンストラクタ渡し
	C_Draw3D_Base2* Get_Draw(const int *BulletDrawNo, const D3DXMATRIX *Mat);



protected:

private:
	C_Draw3D_Base2 *DrawNo0(const D3DXMATRIX *Mat);
};