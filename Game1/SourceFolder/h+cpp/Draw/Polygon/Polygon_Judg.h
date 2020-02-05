#pragma once
#include"../../Draw3DBase/Car_Parts_Joint.h"

class C_Car_Parts_Judg_Polygon :public C_Car_Parts_Joint
{
public:
	C_Car_Parts_Judg_Polygon(const S_CAR_PARTS_DATA *Data,
		const D3DXVECTOR3* Pos_A, const D3DXVECTOR3* Pos_B, const D3DXVECTOR3* Pos_C, const D3DXVECTOR3* Pos_D);
protected:

};