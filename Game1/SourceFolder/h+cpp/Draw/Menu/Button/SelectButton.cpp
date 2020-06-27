#include "SelectButton.h"
#include"../../MaterialManager/TextureManager.h"
#include"../../Scene/SceneNo.h"

extern TextureManager textureManager;

c_SelectButton::c_SelectButton(const D3DXVECTOR3 * pos, const float PosY)
{
	nextNo = co_StageSelectScene;

	//‰æ‘œ‚Ìƒ[ƒh
	width = 453;
	height = 92;
	buttonTex[0] = textureManager.GetTexture("CharSelect1.png", width, height, NULL);

	width2 = 467;
	height2 = 106;
	buttonTex[1] = textureManager.GetTexture("CharSelect1-2.png", width2, height2, NULL);

	// ˆÊ’u‚Ì‰Šú‰»
	basePos = *pos;
	transPos = D3DXVECTOR3(5.0f, PosY, 0.0f);
	Pos = basePos + transPos;

	// Šgk‚Ì‰Šú‰»
	InitScal(6, 50.0f);
}
