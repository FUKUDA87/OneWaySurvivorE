#include "Hpbar2DPlayer.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// �X�v���C�g

c_Hpbar2DPlayer::c_Hpbar2DPlayer()
{
	Pos = D3DXVECTOR2(0.0f, 0.0f);
	ScalPos = D3DXVECTOR2(300.0f, 30.0f);

	//�΃o�[
	hpTex[1] = { NULL,1,1};
	hpTex[1].Tex = textureManager.GetTexture("plaHp.png", hpTex[1].Width, hpTex[1].Height, NULL);

	numDraw = new c_Num2DBase(1);
	InitVec.x = (float)hpTex[0].Width*ScalPos.x;
	InitVec.y = (float)hpTex[0].Height*ScalPos.y;
	InitVec /= 2.0f;

	//�΃o�[
	slash.Width = 18;
	slash.Height = 28;
	slash.Tex = textureManager.GetTexture("slash2.png", slash.Width, slash.Height, NULL);
}

c_Hpbar2DPlayer::~c_Hpbar2DPlayer()
{
	if (numDraw != nullptr)delete numDraw;
}

void c_Hpbar2DPlayer::Draw2D(const int * NowHp, const int * MaxHp)
{
	// Hpbar�̕\��
	DrawA(NowHp, MaxHp);

	// /�̕\��
	RECT rcslash = { 0,0,slash.Width,slash.Height };
	D3DXMATRIX tmpMat, ScalMat;
	D3DXVECTOR2 pos,scalPos = D3DXVECTOR2((float)slash.Width, (float)slash.Height);
	D3DXVec2Normalize(&scalPos, &scalPos);
	scalPos *= 14.0f;
	pos = D3DXVECTOR2(Pos.x + InitVec.x, Pos.y + InitVec.y);
	D3DXMatrixTranslation(&tmpMat, pos.x, pos.y, NULL);
	D3DXMatrixScaling(&ScalMat, scalPos.x / (float)slash.Width, scalPos.y / (float)slash.Height, NULL);
	tmpMat = ScalMat * tmpMat;
	lpSprite->SetTransform(&tmpMat);
	lpSprite->Draw(slash.Tex, &rcslash, &D3DXVECTOR3((float)slash.Width / 2.0f, (float)slash.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Hp�̐��l�̕\��
	if (numDraw == nullptr)return;

	bool RevFlg = true;
	float Size = 16.0f, xUp = 1.0f;
	D3DXVECTOR2 drawPos = D3DXVECTOR2(pos.x - scalPos.x / 2.0f - xUp, pos.y - scalPos.y / 2.0f);
	numDraw->Draw(NowHp, &drawPos, &Size, &RevFlg);

	RevFlg = false;
	drawPos.x = pos.x + scalPos.x / 2.0f+ xUp;
	numDraw->Draw(MaxHp, &drawPos, &Size, &RevFlg);

}
