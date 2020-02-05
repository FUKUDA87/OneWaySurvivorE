#include "Hp_New.h"

C_Hp_Draw_New::~C_Hp_Draw_New()
{
	Hp_Delete();
}

void C_Hp_Draw_New::Hp_Init(C_HpBase * InitHpBase)
{
	Hp_Delete();

	HpBase = InitHpBase;
}

void C_Hp_Draw_New::Hp_Delete(void)
{
	if (HpBase != nullptr) {
		delete HpBase;
	}
}

void C_Hp_Draw_New::Hp_Draw2D(void)
{
	if (HpBase != nullptr) {
		HpBase->Draw2DAll(&CharaBase.NowHp, &CharaBase.MaxHp);
	}
}

void C_Hp_Draw_New::Hp_Draw3D(const D3DXVECTOR3 * CamPos, const D3DXMATRIX * Mat, const float UpY)
{
	if (HpBase != nullptr) {
		HpBase->Draw3DAll(&CharaBase.NowHp, &CharaBase.MaxHp, CamPos, Mat, UpY);
	}
}
