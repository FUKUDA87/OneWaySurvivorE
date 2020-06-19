#include "FadeDraw.h"
#include"../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// �X�v���C�g

#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight

C_FadeDraw::C_FadeDraw()
{
	fadeTex = textureManager.GetTexture("h.png", 3, 3, NULL);
}

void C_FadeDraw::Draw(const int * a, const int * r, const int * g, const int * b)
{
	RECT rcH = { 1,1,2,2 };
	D3DXMATRIX scalMat;
	D3DXMatrixScaling(&scalMat, SCRW, SCRH, 1.0f);
	lpSprite->SetTransform(&scalMat);
	lpSprite->Draw(fadeTex, &rcH, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(*a, *r, *g, *b));
}

void C_FadeDraw::Draw(const int * a, const int * Color)
{
	Draw(a, Color, Color, Color);
}
