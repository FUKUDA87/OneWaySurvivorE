#include "Num2DA.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// �X�v���C�g

C_Num2DA::C_Num2DA(const D3DXVECTOR3 * Pos, const D3DXVECTOR3 * Scal)
{
	//������
	pos = *Pos;
	scalPos = *Scal;
	
	// �摜�̃��[�h
	NumTex.Width = 500;
	NumTex.Height = 50;
	NumTex.Tex = textureManager.GetTexture("CharNum2.png", NumTex.Width, NumTex.Height, NULL);
}

void C_Num2DA::Draw2D(const int * TmpNum)
{
	//���̕\��--------------------------------------------------------------------------
	int w = NumTex.Width / 10, h = NumTex.Height;
	RECT rcNum[] = {
	{0 + w * 0,0,w + w * 0,h},
	{0 + w * 1,0,w + w * 1,h},
	{0 + w * 2,0,w + w * 2,h},
	{0 + w * 3,0,w + w * 3-3,h},
	{0 + w * 4,0,w + w * 4,h},
	{0 + w * 5,0,w + w * 5,h},
	{0 + w * 6,0,w + w * 6,h},
	{0 + w * 7+2,0,w + w * 7,h},
	{0 + w * 8,0,w + w * 8+2,h},
	{0 + w * 9+2,0,w + w * 9,h} };

	//���̓ǂݍ���
	char cScore[64];
	sprintf_s(cScore, sizeof(cScore), "%d", *TmpNum);
	int i;
	for (i = 0; cScore[i] != '\0'; i++);

	//�ʒu�̃Z�b�g
	Judg judg;
	D3DXMATRIX tmpMat,ScalMat;
	judg.Set_TransMat(&tmpMat, &pos);
	D3DXMatrixScaling(&ScalMat, scalPos.x, scalPos.y, NULL);

	//���̕\��
	int s = i;
	for (i -= 1; i >= 0; i--) {
		//�������Q�̎��̍s��쐬
		D3DXMATRIX TransMat;
		D3DXVECTOR3 TransPos;
		if (s > 1) {
			if (i == 0) {
				TransPos = D3DXVECTOR3((float)(rcNum[cScore[i] - '0'].left- rcNum[cScore[i] - '0'].right)/2.0f*scalPos.x,0.0f , 0.0f);
			}
			else {
				TransPos = D3DXVECTOR3((float)(rcNum[cScore[i] - '0'].right - rcNum[cScore[i] - '0'].left) / 2.0f*scalPos.x,0.0f, 0.0f);
			}
		}
		else {
			TransPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		judg.Set_TransMat(&TransMat, &TransPos);
		TransMat = TransMat * tmpMat;

		D3DXMATRIX DrawMat = ScalMat * TransMat;
		lpSprite->SetTransform(&DrawMat);
		lpSprite->Draw(NumTex.Tex, &rcNum[cScore[i] - '0'], &D3DXVECTOR3((float)w / 2.0f, (float)h / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

