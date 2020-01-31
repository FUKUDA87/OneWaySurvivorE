#pragma once
#include"../../../Draw3DBase/PartsBase.h"

class C_PartsDraw_Gun :public C_PartsBase {
public:
	C_PartsDraw_Gun(C_Draw3D_Base2 *NewDraw,const S_Gun_Parts_Data *Data);

	S_Gun_Parts_Data Get_M_Data(void) {
		return M_Data;
	}

	D3DXVECTOR3 Get_Gun_Mouth_Pos(void);

	void Set_Mat(const D3DXMATRIX *Mat);

	//�e������Flg
	bool Get_Bullet_Shot_Flg(void);

	D3DXMATRIX Get_Parts_TransMat(void);
protected:
	//�e�̃p�[�c���
	S_Gun_Parts_Data M_Data;
private:
	//������

	void Set_Parts_Data(const S_Gun_Parts_Data *Data);
};