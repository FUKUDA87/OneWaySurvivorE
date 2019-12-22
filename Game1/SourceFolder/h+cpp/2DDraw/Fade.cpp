#include "Fade.h"

void Fade::Init()
{
	fade.TEX = { NULL,3,3,NULL,NULL,NULL };
	fade.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/h.png", fade.TEX.Width, fade.TEX.Height, NULL);
	fade.Base.Flg = false;
	out = false;
	SetColor(true, false);
}

Fade::Fade()
{
	Init();
	static bool Flg = true;
	if (Flg == true) {
		FadeMove = new C_FadeNoMove();
		MoveFlg = false;
		alpha = 0;
		Flg = false;
	}
	else {
		FadeMove = new C_FadeOut();
		MoveFlg = true;
		alpha = 255;
	}
}

Fade::~Fade()
{
	if (FadeMove != nullptr) {
		delete FadeMove;
	}
}

bool Fade::Update()
{
	C_FadeMove *Move;
	MoveEndFlg = MoveFlg;
	Move=FadeMove->Action(&MoveFlg, &alpha, 6);
	if (Move != nullptr) {
		delete FadeMove;
		FadeMove = Move;
	}
	return MoveFlg;
}

void Fade::ChaFlg(bool b)
{
	fade.Base.Flg = b;
	if (b == false) {
		out = b;
	}
}

void Fade::Draw()
{
	RECT rcH = { 1,1,2,2 };
	D3DXMATRIX scalMat;
	D3DXMatrixScaling(&scalMat, SCRW, SCRH, 1.0f);
	lpSprite->SetTransform(&scalMat);
	lpSprite->Draw(fade.TEX.Tex, &rcH, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(alpha, FadeColor, FadeColor, FadeColor));//
}

void Fade::Draw(int Color)
{
	RECT rcH = { 1,1,2,2 };
	D3DXMATRIX scalMat;
	D3DXMatrixScaling(&scalMat, SCRW, SCRH, 1.0f);
	lpSprite->SetTransform(&scalMat);
	lpSprite->Draw(fade.TEX.Tex, &rcH, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(alpha, Color, Color, Color));//
}
