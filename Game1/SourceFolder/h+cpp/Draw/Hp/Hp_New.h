#pragma once
#include"HpBase.h"
#include"../../GameSource/CharaBase.h"


class C_Hp_Draw_New :public C_CharaBase {
public:
	~C_Hp_Draw_New();
protected:
	//Hp•\¦‰Šú‰»
	void Hp_Init(C_HpBase* InitHpBase);
	//Hpíœ
	void Hp_Delete(void);
	//Hp‚QD•\¦
	void Hp_Draw2D(void);
	//Hp3D•\¦
	void Hp_Draw3D(const D3DXVECTOR3 *CamPos, const D3DXMATRIX *Mat, const float UpY);
private:
	C_HpBase *HpBase;
};