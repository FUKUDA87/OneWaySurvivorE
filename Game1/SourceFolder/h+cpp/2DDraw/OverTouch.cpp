#include "OverTouch.h"

C_OverTouch::C_OverTouch(const D3DXVECTOR3 * WindPos, const D3DXVECTOR3 * WindScal, const D3DXVECTOR3 * CharScal, const float * yUp, const int * Mode):C_ClearTouch(WindPos,WindScal,CharScal,yUp,Mode)
{
	//初期化
	InitRetry();

	//文字の拡大
	Retry.Base.ScaPos.x *= CharScal->x;
	Retry.Base.ScaPos.y *= CharScal->y;


	//移動の初期化
	Retry.Base.TraPos = D3DXVECTOR3(0.0f, -((float)Retry.TEX.Height*Retry.Base.ScaPos.y / 2.0f + *yUp), 0.0f);
	Stage.Base.TraPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Title.Base.TraPos = D3DXVECTOR3(0.0f, ((float)Title.TEX.Height*Title.Base.ScaPos.y / 2.0f + *yUp), 0.0f);

	//座標の初期化
	Retry.Base.Pos = wind.Base.Pos;
}

C_OverTouch::~C_OverTouch()
{
}

void C_OverTouch::Draw2DAll(void)
{
	Draw2D();
	Draw2DRetry();
	Draw2DTitle();
	Draw2DStage();
}

int C_OverTouch::TouchNow(void)
{
	if (UpdateRetry() == true)return 1;
	if (UpdateStage() == true)return 2;
	if (UpdateTitle() == true)return 3;
	return 0;
}

void C_OverTouch::Draw2DRetry(void)
{
	//位置のセット
	D3DXMatrixTranslation(&Retry.Base.Mat, Retry.Base.Pos.x, Retry.Base.Pos.y, NULL);
	judg.SetTransMat(&Retry.Base.Trans, &Retry.Base.TraPos);
	D3DXMatrixScaling(&Retry.Base.Scal, Retry.Base.ScaPos.x, Retry.Base.ScaPos.y, Retry.Base.ScaPos.z);
	D3DXMATRIX tmp;
	tmp = Retry.Base.Scal*Retry.Base.Trans*Retry.Base.Mat;

	//表示
	if (Retry.Base.DrawFlg == false) {
		RECT rcH = { 0,0, Retry.TEX.Width, Retry.TEX.Height };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Retry.TEX.Tex, &rcH, &D3DXVECTOR3((float)Retry.TEX.Width / 2.0f, (float)Retry.TEX.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
	else {
		RECT rcH = { 0,0, Retry.TEX2.Width, Retry.TEX2.Height };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Retry.TEX2.Tex, &rcH, &D3DXVECTOR3((float)Retry.TEX2.Width / 2.0f, (float)Retry.TEX2.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
}

int C_OverTouch::TouchNow2(void)
{
	int Touch = TouchNow();

	if (Touch != 0) {
		//初期化
		Title.Base.DrawFlg = false;
		Stage.Base.DrawFlg = false;
		Retry.Base.DrawFlg = false;

		if (Touch == 1)Retry.Base.DrawFlg = true;
		if (Touch == 3)Title.Base.DrawFlg = true;
		if (Touch == 2)Stage.Base.DrawFlg = true;

	}

	return Touch;
}

void C_OverTouch::InitRetry(void)
{
	//画像のロード
	Retry.TEX = { NULL,418,92,NULL,NULL,NULL };
	Retry.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharRetry1.png", Retry.TEX.Width, Retry.TEX.Height, NULL);

	Retry.TEX2 = { NULL,432,106,NULL,NULL,NULL };
	Retry.TEX2.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharRetry1-2.png", Retry.TEX2.Width, Retry.TEX2.Height, NULL);

	Retry.Base.DrawFlg = false;

	//拡大の初期化
	int CharNum = 5;
	Retry.Base.ScaPos = D3DXVECTOR3(50.0f*(float)CharNum / (float)Retry.TEX.Width, 50.0f / (float)Retry.TEX.Height, 1.0f);
	//表示数のカウント
	DrawNum += 1;
}

bool C_OverTouch::UpdateRetry(void)
{
	return judg.PlaneCri(judg.SetMatP(Retry.Base.Pos + Retry.Base.TraPos), Retry.Base.ScaPos, Retry.TEX.Width, Retry.TEX.Height);
}
