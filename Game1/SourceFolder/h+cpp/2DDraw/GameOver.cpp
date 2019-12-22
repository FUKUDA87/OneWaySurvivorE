#include "GameOver.h"

GameOver::GameOver()
{
	gaov.TEX = { NULL,502,85,NULL,NULL };
	gaov.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharGameOver3.png", gaov.TEX.Width, gaov.TEX.Height, NULL);
	D3DXMatrixTranslation(&gaov.Base.Mat, (float)SCRW / 2.0f, (float)SCRH / 2.0f, NULL);
	gaov.Base.Flg = false;

	stcl.TEX = { NULL,653,64,NULL,NULL };
	stcl.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharStageClear1.png", stcl.TEX.Width, stcl.TEX.Height, NULL);
	D3DXMatrixTranslation(&stcl.Base.Mat, (float)SCRW / 2.0f, (float)SCRH / 2.0f, NULL);
	stcl.Base.Flg = false;
}

void GameOver::Draw2D()
{
	if (gaov.Base.Flg == true) {
		RECT rcGa = { 0,0,gaov.TEX.Width, gaov.TEX.Height };
		lpSprite->SetTransform(&gaov.Base.Mat);
		lpSprite->Draw(gaov.TEX.Tex, &rcGa, &D3DXVECTOR3((float)gaov.TEX.Width / 2.0f, (float)gaov.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//

	}
	if (stcl.Base.Flg == true) {
		RECT rcGa = { 0,0,stcl.TEX.Width, stcl.TEX.Height };
		lpSprite->SetTransform(&stcl.Base.Mat);
		lpSprite->Draw(stcl.TEX.Tex, &rcGa, &D3DXVECTOR3((float)stcl.TEX.Width / 2.0f, (float)stcl.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
}

bool GameOver::Update(bool CLEor, bool Flg)
{
	if (CLEor == true) {
		if (Flg == true) {
			stcl.Base.Flg = Flg;
			gaov.Base.Flg = false;
			return true;
		}
	}
	else {
		if (Flg == true) {
			gaov.Base.Flg = Flg;
			stcl.Base.Flg = false;
			return true;
		}
	}
	stcl.Base.Flg = false;
	gaov.Base.Flg = false;
	return false;
}

bool GameOver::GetFlg(void)
{
	if (stcl.Base.Flg == true) {
		return true;
	}
	else {
		return false;
	}
	return false;
}
