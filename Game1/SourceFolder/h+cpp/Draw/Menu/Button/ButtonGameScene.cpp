#include "ButtonGameScene.h"
extern LPD3DXSPRITE lpSprite;	// スプライト

c_ButtonGameScene::c_ButtonGameScene()
{
	DrawChangeFlg = false;
}

void c_ButtonGameScene::Draw2D(void)
{
	//位置のセット
	D3DXMATRIX tmp,ScalMat;
	D3DXMatrixTranslation(&tmp, Pos.x, Pos.y, NULL);
	D3DXMatrixScaling(&ScalMat, scalX, scalY, NULL);
	tmp = ScalMat*tmp;
	//表示
	if (DrawChangeFlg == false) {
		RECT rcH = { 0,0, width, height };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(buttonTex[0], &rcH, &D3DXVECTOR3((float)width / 2.0f, (float)height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
	else {
		RECT rcH = { 0,0, width2, height2 };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(buttonTex[1], &rcH, &D3DXVECTOR3(width2 / 2.0f, (float)height2 / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
}

void c_ButtonGameScene::InitScal(const int ChaNum, const float Size)
{
	scalX = Size * (float)ChaNum / (float)width;
	scalY = Size / (float)height;
}
