#include "Num2DA.h"

extern LPD3DXSPRITE lpSprite;	// スプライト

C_Num2DA::C_Num2DA(const D3DXVECTOR3 * Pos, const D3DXVECTOR3 * Scal)
{
	//初期化
	SetNum(Pos, Scal);
	int W = 500, H = 50;
	SetTex("../GameFolder/Material/Texture/CharNum2.png", &W, &H);
}

void C_Num2DA::Draw2DNB(const int * TmpNum)
{
	//数の表示--------------------------------------------------------------------------
	int w = Num.TEX.Width / 10, h = Num.TEX.Height;
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

	//数の読み込み
	char cScore[64];
	sprintf_s(cScore, sizeof(cScore), "%d", *TmpNum);
	int i;
	for (i = 0; cScore[i] != '\0'; i++);

	//位置のセット
	judg.SetTransMat(&Num.Base.Mat, &Num.Base.Pos);

	//数の表示
	int s = i;
	for (i -= 1; i >= 0; i--) {
		//桁数が２の時の行列作成
		D3DXMATRIX TransMat;
		D3DXVECTOR3 TransPos;
		if (s > 1) {
			if (i == 0) {
				TransPos = D3DXVECTOR3((float)(rcNum[cScore[i] - '0'].left- rcNum[cScore[i] - '0'].right)/2.0f*Num.Base.ScaPos.x,0.0f , 0.0f);
			}
			else {
				TransPos = D3DXVECTOR3((float)(rcNum[cScore[i] - '0'].right - rcNum[cScore[i] - '0'].left) / 2.0f*Num.Base.ScaPos.x,0.0f, 0.0f);
			}
		}
		else {
			TransPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		judg.SetTransMat(&TransMat, &TransPos);
		TransMat = TransMat * Num.Base.Mat;

		lpSprite->SetTransform(&GetDrawMatNDB(&TransMat));
		lpSprite->Draw(Num.TEX.Tex, &rcNum[cScore[i] - '0'], &D3DXVECTOR3((float)w / 2.0f, (float)h / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

