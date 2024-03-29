#include "PlayButton.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../Scene/SceneNo.h"

extern TextureManager textureManager;

c_PlayButton::c_PlayButton(const D3DXVECTOR3 * pos, const float PosY)
{
	nextNo = co_PlayGame;

	//画像のロード
	width = 329;
	height = 92;
	buttonTex[0] = textureManager.GetTexture("CharPlay1.png", width, height, NULL);

	width2 = 343;
	height2 = 106;
	buttonTex[1] = textureManager.GetTexture("CharPlay1-2.png", width2, height2, NULL);

	// 位置の初期化
	basePos = *pos;
	transPos = D3DXVECTOR3(0.0f, PosY, 0.0f);
	Pos = basePos + transPos;

	// 拡縮の初期化
	InitScal(4, 50.0f);
}
