#pragma once
#include"../../../Car/Parts/PartsBase.h"

class C_PartsDraw_Gun :public C_PartsBase {
public:
	C_PartsDraw_Gun(C_Draw3D_Base2 *NewDraw,const S_Gun_Parts_Data *Data);

	S_Gun_Parts_Data Get_M_Data(void) {
		return M_Data;
	}

	D3DXVECTOR3 Get_Gun_Mouth_Pos(void);

	void Set_Mat(const D3DXMATRIX *Mat);

	//弾を撃つFlg
	bool Get_Bullet_Shot_Flg(void);

	D3DXMATRIX Get_Parts_TransMat(void);
protected:
	//銃のパーツ情報
	S_Gun_Parts_Data M_Data;
private:
	//初期化

	void Set_Parts_Data(const S_Gun_Parts_Data *Data);
};