#include "Pause.h"
#include"../GameSource/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// �X�v���C�g

#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight

Pause::Pause()
{
	pau.TEX = { NULL,250,50,NULL,NULL,NULL };
	pau.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharPause1.png", pau.TEX.Width, pau.TEX.Height, NULL);
	D3DXMatrixTranslation(&pau.Base.Mat, SCRW / 2.0f, SCRH / 2.0f, 0.0f);
	pau.Base.DrawFlg = false;

	// �������̏�����
	fadeDraw = new C_FadeDraw();
	alpha = 150;

	StageSaveFlg = false;
}

Pause::~Pause()
{
	if (fadeDraw != nullptr)delete fadeDraw;
}

void Pause::Draw()
{
	if (pau.Base.DrawFlg == true) {

		// �������̕\��
		if (fadeDraw != nullptr) {
			int Color = 0;
			fadeDraw->Draw(&alpha, &Color);
		}

		// �|�[�Y�\��
		RECT rcH = { 0,0,pau.TEX.Width,pau.TEX.Height };
		lpSprite->SetTransform(&pau.Base.Mat);
		lpSprite->Draw(pau.TEX.Tex, &rcH, &D3DXVECTOR3((float)pau.TEX.Width / 2.0f, (float)pau.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
}
