#include "RetryButton.h"
#include"../../MaterialManager/TextureManager.h"
#include"../../Scene/SceneNo.h"

extern TextureManager textureManager;

c_RetryButton::c_RetryButton(const D3DXVECTOR3 * pos, const float PosY)
{
	nextNo = co_GameScene;

	//�摜�̃��[�h
	width = 418;
	height = 92;
	buttonTex[0] = textureManager.GetTexture("CharRetry1.png", width, height, NULL);

	width2 = 432;
	height2 = 106;
	buttonTex[1] = textureManager.GetTexture("CharRetry1-2.png", width2, height2, NULL);

	// �ʒu�̏�����
	basePos = *pos;
	transPos = D3DXVECTOR3(0.0f, PosY, 0.0f);
	Pos = basePos + transPos;

	// �g�k�̏�����
	InitScal(5, 50.0f);
}
