#pragma once
#include"HpBase.h"
#include"../../GameSource/CharaBase.h"


class C_Hp_Draw_New :public C_CharaBase {
public:
	~C_Hp_Draw_New();
protected:
	//Hp表示初期化
	void Hp_Init(C_HpBase* InitHpBase);
	//Hp削除
	void Hp_Delete(void);
	//Hp２D表示
	void Hp_Draw2D(void);
	//Hp3D表示
	void Hp_Draw3D(const D3DXVECTOR3 *CamPos, const D3DXMATRIX *Mat, const float UpY);
private:
	C_HpBase *HpBase;
};