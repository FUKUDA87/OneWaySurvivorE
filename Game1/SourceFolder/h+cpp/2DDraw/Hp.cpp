#include "Hp.h"
#include"../GameSource/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height


void HP::Init()
{
	//白いバー
	hp.TEX = { NULL,1,1,NULL,NULL,NULL };
	hp.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/HpH.png",hp.TEX.Width, hp.TEX.Height, NULL);
	hp.Base.ScaPos = D3DXVECTOR3(300,30, 0);
	D3DXMatrixScaling(&hp.Base.Scal, hp.Base.ScaPos.x, hp.Base.ScaPos.y, 0.0f);
	hp.Base.Flg = true;
	hp.Base.Pos = D3DXVECTOR3(SCRW / 2 / 10, SCRH- SCRH / 10, 0);
	//緑バー
	Php.TEX = { NULL,1,1,NULL,NULL,NULL };
	Php.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/plaHp.png", Php.TEX.Width, Php.TEX.Height, NULL);
	Php.Base.ScaPos = hp.Base.ScaPos;
	D3DXMatrixScaling(&Php.Base.Scal, Php.Base.ScaPos.x, Php.Base.ScaPos.y, 0.0f);
	Php.Base.Flg = hp.Base.Flg;
	Php.Base.Pos = hp.Base.Pos;
}

bool HP::Update(int Max,int nowHp, bool disp)
{
	if (nowHp <= 0) {
		if (disp == false) {
			Php.Base.Flg = hp.Base.Flg = false;
			return false;
		}
	}
	float per;
	if (nowHp < Max) {
		per = ((float)nowHp) / ((float)Max);
		if (per < 0.0f) {
			per = 0.0f;
		}
	}
	else {
		per = 1.0f;
	}
	Php.Base.ScaPos.x = hp.Base.ScaPos.x*per;
	D3DXMatrixScaling(&Php.Base.Scal, Php.Base.ScaPos.x, Php.Base.ScaPos.y, 0.0f);
	return true;
}

void HP::Draw()
{
	if (hp.Base.Flg == true) {
		RECT rcAim = { 0,0,1,1 };
		D3DXMatrixTranslation(&hp.Base.Mat, hp.Base.Pos.x, hp.Base.Pos.y, NULL);
		D3DXMATRIX tmp;
		tmp = hp.Base.Scal * hp.Base.Mat;
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(hp.TEX.Tex, &rcAim, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(20, 255, 255, 255));
	}
	if (Php.Base.Flg == true) {
		RECT rcAim = { 0,0,1,1 };
		D3DXMatrixTranslation(&Php.Base.Mat, Php.Base.Pos.x, Php.Base.Pos.y, NULL);
		D3DXMATRIX tmp;
		tmp = Php.Base.Scal * Php.Base.Mat;
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Php.TEX.Tex, &rcAim, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}
