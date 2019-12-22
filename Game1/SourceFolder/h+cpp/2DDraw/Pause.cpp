#include "Pause.h"

Pause::Pause()
{
	pau.TEX = { NULL,250,50,NULL,NULL,NULL };
	pau.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharPause1.png", pau.TEX.Width, pau.TEX.Height, NULL);
	D3DXMatrixTranslation(&pau.Base.Mat, SCRW / 2.0f, SCRH / 2.0f, 0.0f);
	pau.Base.DrawFlg = false;
	alpha = 150;

	StageSaveFlg = false;
}

void Pause::Draw2DPau()
{
	if (pau.Base.DrawFlg == true) {
		Draw(0);
		RECT rcH = { 0,0,pau.TEX.Width,pau.TEX.Height };
		lpSprite->SetTransform(&pau.Base.Mat);
		lpSprite->Draw(pau.TEX.Tex, &rcH, &D3DXVECTOR3((float)pau.TEX.Width / 2.0f, (float)pau.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
}

bool Pause::UpdatePau()
{
	alpha = 150;
	return true;
}
