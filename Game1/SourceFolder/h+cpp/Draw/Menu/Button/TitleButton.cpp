#include "TitleButton.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../Scene/SceneNo.h"

extern TextureManager textureManager;

c_TitleButton::c_TitleButton(const D3DXVECTOR3 *pos, const float PosY)
{
	nextNo = co_TitleScene;

	//�摜�̃��[�h
	width = 350;
	height = 92;
	buttonTex[0] = textureManager.GetTexture("CharTitle1.png", width, height, NULL);

	width2 = 364;
	height2 = 106;
	buttonTex[1] = textureManager.GetTexture("CharTitle1-2.png", width2, height2, NULL);

	// �ʒu�̏�����
	basePos = *pos;
	transPos = D3DXVECTOR3(0.0f, PosY, 0.0f);
	Pos = basePos + transPos;
	
	// �g�k�̏�����
	InitScal(5, 50.0f);

}
