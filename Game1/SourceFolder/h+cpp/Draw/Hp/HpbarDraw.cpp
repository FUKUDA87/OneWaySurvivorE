#include "HpbarDraw.h"

C_HpbarDraw::~C_HpbarDraw()
{
	Delete();
}

void C_HpbarDraw::Init(C_HpBase * InitHpBase)
{
	Delete();

	HpBase = InitHpBase;
}

void C_HpbarDraw::Delete(void)
{
	if (HpBase == nullptr)return;
		
	delete HpBase;
	
}

void C_HpbarDraw::Draw2D(const CHARABASE * CharaBase)
{
	if (HpBase == nullptr)return;

	HpBase->Draw2DAll(&CharaBase->NowHp, &CharaBase->MaxHp);
}

void C_HpbarDraw::Draw3D(const CHARABASE * CharaBase, const D3DXVECTOR3 * CamPos, const D3DXMATRIX * Mat, const float UpY)
{
	if (HpBase == nullptr)return;

	HpBase->Draw3DAll(&CharaBase->NowHp, &CharaBase->MaxHp, CamPos, Mat, UpY);
}
