#include "Score.h"
#include"../GameSource/TextureManager.h"
#include"../GameSource/Judgment.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;
extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

C_Score::C_Score()
{
	Init();
}

C_Score::~C_Score()
{
}

void C_Score::Init(void)
{
	//スコア文字画像ロード
	score.TEX = { NULL,612,147,NULL,NULL,NULL };
	score.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharScore1.png", score.TEX.Width, score.TEX.Height, NULL);
	//スコア数画像ロード
	snum.TEX = { NULL,1511,178,NULL,NULL,NULL };
	snum.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/Num1.png", snum.TEX.Width, snum.TEX.Height, NULL);
	//スコアの＋－画像のロード
	sPoint.TEX = { NULL,192,112,NULL,NULL,NULL };
	sPoint.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharPM1.png", sPoint.TEX.Width, sPoint.TEX.Height, NULL);
	//拡大の初期化
	D3DXVECTOR2 sPos = D3DXVECTOR2(50.0f, 50.0f);
	score.Base.ScaPos = D3DXVECTOR3(sPos.x*5.0f / (float)score.TEX.Width, sPos.y / (float)score.TEX.Height, 0.0f);
	snum.Base.ScaPos = D3DXVECTOR3(sPos.x*10.0f / (float)snum.TEX.Width, sPos.y / (float)snum.TEX.Height, 0.0f);
	sPoint.Base.ScaPos = D3DXVECTOR3(sPos.x*2.0f / (float)sPoint.TEX.Width, sPos.y / (float)sPoint.TEX.Height, 0.0f);
	//サイズ変更
	score.Base.ScaPos *= 0.9f;
	snum.Base.ScaPos *= 0.9f;
	sPoint.Base.ScaPos *= 0.9f;
	//拡大行列
	Judg judg;

	judg.ScalingMat(&score.Base.Scal, &score.Base.ScaPos);
	judg.ScalingMat(&snum.Base.Scal, &snum.Base.ScaPos);
	judg.ScalingMat(&sPoint.Base.Scal, &sPoint.Base.ScaPos);

	//スコア数の初期化
	ScoreNum = 0;
	ScoreNumNow = 0;

	//位置の初期設定
	D3DXMatrixTranslation(&score.Base.Mat, 1280.0f- score.Base.ScaPos.x*(float)score.TEX.Width, 0.0f, 0.0f);

	D3DXMatrixTranslation(&snum.Base.Trans,-snum.Base.ScaPos.x*(float)snum.TEX.Width / 10.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&snum.Base.Mat, 1280.0f, score.Base.Mat._42+ score.Base.ScaPos.y * (float)score.TEX.Height, 0.0f);

	//スコアが下がる初期化
	sPoint.Base.DrawFlg = false;
	Anime = 0.0f;
}

bool C_Score::Update(void)
{
	//スコアを上げて行く処理
	if (ScoreNumNow < ScoreNum) {
		int UpNum;
		if ((ScoreNum - ScoreNumNow) >= 10) {
			UpNum = 10;
			ScoreNumNow += UpNum;
		}
		else {
			ScoreNumNow = ScoreNum;
		}
	}
	else {
		ScoreNumNow = ScoreNum;
	}
	//下がり値のアニメーション
	if (sPoint.Base.DrawFlg == true) {
		//アニメーション
		Judg judg;

		if (judg.Quaternion(&sPoint.Base.Mat, StartMat, EndMat, &Anime, AnimeFrame, true) == false) {
			DrawCount -= 1;
			if (DrawCount <= 0) {
				sPoint.Base.DrawFlg = false;
			}
		}
		alphaP = (int)(255.0f*Anime);
	}
	return true;
}

void C_Score::Draw2D(void)
{
	Update();

	char cScore[64];
	int i;
	D3DXMATRIX Trans;

	//スコア文字表示
	RECT rcScore = { 0,0, score.TEX.Width, score.TEX.Height };
	D3DXMATRIX Tmp;
	Tmp = score.Base.Scal*score.Base.Mat;
	lpSprite->SetTransform(&Tmp);
	lpSprite->Draw(score.TEX.Tex, &rcScore, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//スコア数表示
	RECT rcSnum[] = {
		{snum.TEX.Width / 10 * 0,0, snum.TEX.Width / 10 * 1, snum.TEX.Height},
		{snum.TEX.Width / 10 * 1,0, snum.TEX.Width / 10 * 2, snum.TEX.Height},
		{snum.TEX.Width / 10 * 2,0, snum.TEX.Width / 10 * 3, snum.TEX.Height},
		{snum.TEX.Width / 10 * 3,0, snum.TEX.Width / 10 * 4, snum.TEX.Height},
		{snum.TEX.Width / 10 * 4,0, snum.TEX.Width / 10 * 5 + 5 , snum.TEX.Height},
		{snum.TEX.Width / 10 * 5 + 11,0, snum.TEX.Width / 10 * 6, snum.TEX.Height},
		{snum.TEX.Width / 10 * 6,0, snum.TEX.Width / 10 * 7, snum.TEX.Height},
		{snum.TEX.Width / 10 * 7,0, snum.TEX.Width / 10 * 8, snum.TEX.Height},
		{snum.TEX.Width / 10 * 8,0, snum.TEX.Width / 10 * 9, snum.TEX.Height},
		{snum.TEX.Width / 10 * 9,0, snum.TEX.Width / 10 * 10, snum.TEX.Height},
	};

	//下がりの表示
	if (sPoint.Base.DrawFlg == true) {
		//数値の表示
		sprintf_s(cScore, sizeof(cScore), "%d", ScoreNumUD);
		for (i = 0; cScore[i] != '\0'; i++);
		Trans = sPoint.Base.Mat;
		for (i -= 1; i >= 0; i--) {
			Trans = snum.Base.Trans*Trans;
			if ((cScore[i] - '0') == 4) {
				D3DXMATRIX Mat;
				D3DXMatrixTranslation(&Mat, -5.0f, 0.0f, 0.0f);
				Trans = Mat * Trans;
			}
			Tmp = snum.Base.Scal*Trans;
			lpSprite->SetTransform(&Tmp);
			lpSprite->Draw(snum.TEX.Tex, &rcSnum[cScore[i] - '0'], &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(alphaP, 255, 50, 50));//D3DCOLOR_ARGB(alphaP, 255, 255, 255)
		}
		//マイナスの表示
		RECT rcMai[] = {
			{sPoint.TEX.Width / 2 * 0,0, sPoint.TEX.Width / 2 * 1, snum.TEX.Height},
			{sPoint.TEX.Width / 2 * 1,0, sPoint.TEX.Width / 2 * 2, snum.TEX.Height}
		};
		Trans = snum.Base.Trans*Trans;
		Tmp = sPoint.Base.Scal*Trans;
		lpSprite->SetTransform(&Tmp);
		lpSprite->Draw(sPoint.TEX.Tex, &rcMai[1], &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(alphaP, 255, 50, 50));
	}

	//スコア数を文字にする処理
	sprintf_s(cScore, sizeof(cScore), "%d", ScoreNumNow);
	for (i = 0; cScore[i] != '\0'; i++);

	//位分繰り返す
	Trans= snum.Base.Mat;
	for (i -= 1; i >= 0; i--) {
		Trans = snum.Base.Trans*Trans;
		if ((cScore[i] - '0') == 4) {
			D3DXMATRIX Mat;
			D3DXMatrixTranslation(&Mat, -5.0f, 0.0f, 0.0f);
			Trans = Mat * Trans;
		}
		Tmp = snum.Base.Scal*Trans;
		lpSprite->SetTransform(&Tmp);
		lpSprite->Draw(snum.TEX.Tex, &rcSnum[cScore[i] - '0'], &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void C_Score::ScoreUp(const int * UpNum)
{
	//スコア増減判定
	if (*UpNum > 0) {
		//スコアが上がる
		ScoreNum += *UpNum;
	}
	else {
		//スコアが下がる
		ScoreNum += *UpNum;
		if (ScoreNum < 0)ScoreNum = 0;
		//アニメーションの初期化
		if (ScoreNumNow > 0) {
			Anime = 0.0f;
			AnimeFrame = 0.03f;
			ScoreNumUD = *UpNum*-1;
			DrawCount = 15;
			StartMat = snum.Base.Mat;
			D3DXMatrixTranslation(&sPoint.Base.Trans, 0.0f, snum.Base.ScaPos.y * (float)snum.TEX.Height, 0.0f);
			EndMat = sPoint.Base.Trans*StartMat;
			sPoint.Base.DrawFlg = true;
			alphaP = 0;
		}
	}
}
