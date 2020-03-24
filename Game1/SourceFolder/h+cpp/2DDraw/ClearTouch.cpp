#include "ClearTouch.h"
#include"../GameSource/TextureManager.h"

extern TextureManager textureManager;


C_ClearTouch::C_ClearTouch(const D3DXVECTOR3 * WindPos, const D3DXVECTOR3 * WindScal, const D3DXVECTOR3 * CharScal, const float *yUp, const int *Mode)
{
	MenuMode = *Mode;

	//ウィンドウの設定
	wind.Base.Pos = *WindPos;
	wind.Base.ScaPos.x *= WindScal->x;
	wind.Base.ScaPos.y *= WindScal->y;

	//画像のロード
	InitTitle();
	InitStage();

	//文字の拡大
	Title.Base.ScaPos.x *= CharScal->x;
	Title.Base.ScaPos.y *= CharScal->y;
	Stage.Base.ScaPos.x *= CharScal->x;
	Stage.Base.ScaPos.y *= CharScal->y;

	//移動の初期化
	Title.Base.TraPos = D3DXVECTOR3(0.0f, ((float)Title.TEX.Height*Title.Base.ScaPos.y / 2.0f + *yUp), 0.0f);
	Stage.Base.TraPos = D3DXVECTOR3(0.0f, -((float)Stage.TEX.Height*Stage.Base.ScaPos.y / 2.0f + *yUp), 0.0f);
	//座標の初期化
	Title.Base.Pos = wind.Base.Pos;
	Stage.Base.Pos = wind.Base.Pos;
}

C_ClearTouch::~C_ClearTouch()
{
}

bool C_ClearTouch::UpdateAll(void)
{
	return true;
}

void C_ClearTouch::Draw2DAll(void)
{
	Draw2D();
	Draw2DTitle();
	Draw2DStage();
}

int C_ClearTouch::TouchNow(void)
{
	if (UpdateTitle() == true)return 1;
	if (UpdateStage() == true)return 2;
	return 0;
}

int C_ClearTouch::TouchNow2(void)
{
	int Touch = TouchNow();

	if (Touch != 0) {
		//初期化
		Title.Base.DrawFlg = false;
		Stage.Base.DrawFlg = false;

		if (Touch == 1)Title.Base.DrawFlg = true;
		if (Touch == 2)Stage.Base.DrawFlg = true;

	}

	return Touch;
}

void C_ClearTouch::InitTitle(void)
{
	//画像のロード
	Title.TEX = { NULL,350,92,NULL,NULL,NULL };
	Title.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharTitle1.png", Title.TEX.Width, Title.TEX.Height, NULL);

	Title.TEX2 = { NULL,364,106,NULL,NULL,NULL };
	Title.TEX2.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharTitle1-2.png", Title.TEX2.Width, Title.TEX2.Height, NULL);

	Title.Base.DrawFlg = false;

	int CharNum = 5;
	Title.Base.ScaPos = D3DXVECTOR3(50.0f*(float)CharNum / (float)Title.TEX.Width, 50.0f / (float)Title.TEX.Height, 1.0f);
	DrawNum += 1;
}

void C_ClearTouch::Draw2DTitle(void)
{
	//位置のセット
	D3DXMatrixTranslation(&Title.Base.Mat, Title.Base.Pos.x, Title.Base.Pos.y, NULL);
	judg.Set_TransMat(&Title.Base.Trans, &Title.Base.TraPos);
	D3DXMatrixScaling(&Title.Base.Scal, Title.Base.ScaPos.x, Title.Base.ScaPos.y, Title.Base.ScaPos.z);
	D3DXMATRIX tmp;
	tmp = Title.Base.Trans*Title.Base.Mat;
	tmp = Title.Base.Scal*tmp;

	//表示
	if (Title.Base.DrawFlg == false) {
		RECT rcH = { 0,0, Title.TEX.Width, Title.TEX.Height };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Title.TEX.Tex, &rcH, &D3DXVECTOR3((float)Title.TEX.Width / 2.0f, (float)Title.TEX.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
	else {
		RECT rcH = { 0,0, Title.TEX2.Width, Title.TEX2.Height };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Title.TEX2.Tex, &rcH, &D3DXVECTOR3((float)Title.TEX2.Width / 2.0f, (float)Title.TEX2.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
}

bool C_ClearTouch::UpdateTitle(void)
{
	return judg.PlaneCri(judg.SetMatP(&(Title.Base.Pos + Title.Base.TraPos)), Title.Base.ScaPos, Title.TEX.Width, Title.TEX.Height);
}

void C_ClearTouch::InitStage(void)
{
	//画像のロード
	Stage.TEX = { NULL,453,92,NULL,NULL,NULL };
	Stage.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharSelect1.png", Stage.TEX.Width, Stage.TEX.Height, NULL);

	Stage.TEX2 = { NULL,467,106,NULL,NULL,NULL };
	Stage.TEX2.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharSelect1-2.png", Stage.TEX2.Width, Stage.TEX2.Height, NULL);

	Stage.Base.DrawFlg = false;

	//表示の拡大
	int CharNum = 6;
	Stage.Base.ScaPos = D3DXVECTOR3(50.0f*(float)CharNum / (float)Stage.TEX.Width, 50.0f / (float)Stage.TEX.Height, 1.0f);
	DrawNum += 1;
}

void C_ClearTouch::Draw2DStage(void)
{
	//位置のセット
	D3DXMatrixTranslation(&Stage.Base.Mat, Stage.Base.Pos.x, Stage.Base.Pos.y, NULL);
	judg.Set_TransMat(&Stage.Base.Trans, &Stage.Base.TraPos);
	D3DXMatrixScaling(&Stage.Base.Scal, Stage.Base.ScaPos.x, Stage.Base.ScaPos.y, Stage.Base.ScaPos.z);
	D3DXMATRIX tmp;
	tmp = Stage.Base.Scal*Stage.Base.Trans*Stage.Base.Mat;

	//表示
	if (Stage.Base.DrawFlg == false) {
		RECT rcH = { 0,0, Stage.TEX.Width, Stage.TEX.Height };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Stage.TEX.Tex, &rcH, &D3DXVECTOR3((float)Stage.TEX.Width / 2.0f, (float)Stage.TEX.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
	else {
		RECT rcH = { 0,0, Stage.TEX2.Width, Stage.TEX2.Height };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Stage.TEX2.Tex, &rcH, &D3DXVECTOR3((float)Stage.TEX2.Width / 2.0f, (float)Stage.TEX2.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
}

bool C_ClearTouch::UpdateStage(void)
{
	return judg.PlaneCri(judg.SetMatP(&(Stage.Base.Pos + Stage.Base.TraPos)), Stage.Base.ScaPos, Stage.TEX.Width, Stage.TEX.Height);
}

