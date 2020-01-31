#pragma once
#include"../NewGun/GunLaser.h"

class C_Gun_Gatling :public C_GunLaser {
public:
	C_Gun_Gatling(C_GunMoveBase_A *Move);
protected:
	S_Gun_Parts_Data Get_Data_Set(const bool BulletFlg, const D3DXVECTOR3 *TransPos, const D3DXVECTOR3* MouthPos, const int Rate, const int BulletNo, const int CategoryNo);
private:

};