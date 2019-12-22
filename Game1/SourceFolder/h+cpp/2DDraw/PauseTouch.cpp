#include "PauseTouch.h"
#include"../GameSource/TextureManager.h"

extern TextureManager textureManager;


C_PauseTouch::C_PauseTouch(const D3DXVECTOR3 * WindPos, const D3DXVECTOR3 * WindScal, const D3DXVECTOR3 * CharScal, const float *yUp, const int *Mode)
{
	MenuMode = *Mode;

	wind.Base.Pos = *WindPos;
	wind.Base.ScaPos.x *= WindScal->x;
	wind.Base.ScaPos.y *= WindScal->y;

	InitPause();
	InitStage();

	//文字の拡大
	Pause.Base.ScaPos.x *= CharScal->x;
	Pause.Base.ScaPos.y *= CharScal->y;
	Stage.Base.ScaPos.x *= CharScal->x;
	Stage.Base.ScaPos.y *= CharScal->y;

	//移動の初期化
	Pause.Base.TraPos = D3DXVECTOR3(0.0f, -((float)Pause.TEX.Height*Pause.Base.ScaPos.y / 2.0f+*yUp), 0.0f);
	Stage.Base.TraPos = D3DXVECTOR3(0.0f, ((float)Stage.TEX.Height*Stage.Base.ScaPos.y / 2.0f + *yUp), 0.0f);

	Pause.Base.Pos = wind.Base.Pos;
	Stage.Base.Pos = wind.Base.Pos;
}

C_PauseTouch::~C_PauseTouch()
{
}

bool C_PauseTouch::UpdateAll(void)
{
	return true;
}

void C_PauseTouch::Draw2DAll(void)
{
	Draw2D();
	Draw2DPause();
	Draw2DStage();
}

int C_PauseTouch::TouchNow(void)
{
	if (UpdatePause() == true)return 1;
	if (UpdateStage() == true)return 2;
	return 0;
}

void C_PauseTouch::InitPause(void)
{
	//画像のロード
	Pause.TEX = { NULL,329,92,NULL,NULL,NULL };
	Pause.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharPlay1.png", Pause.TEX.Width, Pause.TEX.Height, NULL);

	Pause.TEX2 = { NULL,343,106,NULL,NULL,NULL };
	Pause.TEX2.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharPlay1-2.png", Pause.TEX2.Width, Pause.TEX2.Height, NULL);

	Pause.Base.DrawFlg = false;

	//拡大の初期化
	int CharNum = 4;
	Pause.Base.ScaPos = D3DXVECTOR3(50.0f*(float)CharNum / (float)Pause.TEX.Width, 50.0f / (float)Pause.TEX.Height, 1.0f);
	DrawNum += 1;
}

void C_PauseTouch::Draw2DPause(void)
{
	//位置のセット
	D3DXMatrixTranslation(&Pause.Base.Mat, Pause.Base.Pos.x, Pause.Base.Pos.y, NULL);
	judg.SetTransMat(&Pause.Base.Trans, &Pause.Base.TraPos);
	D3DXMatrixScaling(&Pause.Base.Scal, Pause.Base.ScaPos.x, Pause.Base.ScaPos.y, Pause.Base.ScaPos.z);
	D3DXMATRIX tmp;
	tmp = Pause.Base.Trans*Pause.Base.Mat;
	tmp = Pause.Base.Scal*tmp;
	//表示
	if (Pause.Base.DrawFlg == false) {
		RECT rcH = { 0,0, Pause.TEX.Width, Pause.TEX.Height };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Pause.TEX.Tex, &rcH, &D3DXVECTOR3((float)Pause.TEX.Width / 2.0f, (float)Pause.TEX.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
	else {
		RECT rcH = { 0,0, Pause.TEX2.Width, Pause.TEX2.Height };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Pause.TEX2.Tex, &rcH, &D3DXVECTOR3((float)Pause.TEX2.Width / 2.0f, (float)Pause.TEX2.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
}

bool C_PauseTouch::UpdatePause(void)
{
	return judg.PlaneCri(judg.SetMatP(Pause.Base.Pos+ Pause.Base.TraPos), Pause.Base.ScaPos, Pause.TEX.Width, Pause.TEX.Height);
}

void C_PauseTouch::InitStage(void)
{
	//画像のロード
	Stage.TEX = { NULL,453,92,NULL,NULL,NULL };
	Stage.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharSelect1.png", Stage.TEX.Width, Stage.TEX.Height, NULL);

	Stage.TEX2 = { NULL,467,106,NULL,NULL,NULL };
	Stage.TEX2.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/CharSelect1-2.png", Stage.TEX2.Width, Stage.TEX2.Height, NULL);

	Stage.Base.DrawFlg = false;

	int CharNum = 6;
	Stage.Base.ScaPos = D3DXVECTOR3(50.0f*(float)CharNum / (float)Stage.TEX.Width, 50.0f / (float)Stage.TEX.Height, 1.0f);
	DrawNum += 1;
}

void C_PauseTouch::Draw2DStage(void)
{
	//位置のセット
	D3DXMatrixTranslation(&Stage.Base.Mat, Stage.Base.Pos.x, Stage.Base.Pos.y, NULL);
	judg.SetTransMat(&Stage.Base.Trans, &Stage.Base.TraPos);
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

int C_PauseTouch::TouchNow2(void)
{
	int Touch = TouchNow();

	if (Touch != 0) {
		//初期化
		Pause.Base.DrawFlg = false;
		Stage.Base.DrawFlg = false;

		if(Touch==1)Pause.Base.DrawFlg = true;
		if (Touch == 2)Stage.Base.DrawFlg = true;

	}

	return Touch;
}

bool C_PauseTouch::UpdateStage(void)
{
	return judg.PlaneCri(judg.SetMatP(Stage.Base.Pos+ Stage.Base.TraPos), Stage.Base.ScaPos, Stage.TEX.Width, Stage.TEX.Height);
}
