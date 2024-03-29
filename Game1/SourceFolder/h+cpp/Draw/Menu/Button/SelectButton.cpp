#include "SelectButton.h"
#include"../../MaterialManager/TextureManager.h"
#include"../../Scene/SceneNo.h"

extern TextureManager textureManager;

c_SelectButton::c_SelectButton(const D3DXVECTOR3 * pos, const float PosY)
{
	nextNo = co_StageSelectScene;

	//画像のロード
	width = 453;
	height = 92;
	buttonTex[0] = textureManager.GetTexture("CharSelect1.png", width, height, NULL);

	width2 = 467;
	height2 = 106;
	buttonTex[1] = textureManager.GetTexture("CharSelect1-2.png", width2, height2, NULL);

	// 位置の初期化
	basePos = *pos;
	transPos = D3DXVECTOR3(5.0f, PosY, 0.0f);
	Pos = basePos + transPos;

	// 拡縮の初期化
	InitScal(6, 50.0f);
}
