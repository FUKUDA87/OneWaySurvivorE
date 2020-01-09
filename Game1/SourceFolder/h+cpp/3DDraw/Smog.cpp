#include "Smog.h"
#include"../GameSource/TextureManager.h"
#include"../GameSource/Judgment.h"
#include"../GameSource/InvBi.h"

extern Inv inv;

extern Judg judg;
extern LPDIRECT3DDEVICE9	lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_Smog::C_Smog(const D3DXMATRIX *Mat)
{
	Init();

	smog.Base.Mat = *Mat;

	Init_Mat();

	Init_Num();
}

C_Smog::C_Smog(const D3DXMATRIX * Mat, const S_Smog * H_Smog)
{
	Init();

	smog.Base.Mat = *Mat;

	M_S_Smog = *H_Smog;

	Init_Mat();
}

C_Smog::~C_Smog()
{
}

void C_Smog::Init()
{
	smog.TEX = { NULL,256,256,NULL,NULL,NULL };
	smog.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/Smoke.png", smog.TEX.Width, smog.TEX.Height, NULL);
	//時限の初期化
	NowCount = 1;

	ScalSize = 0.0f;
}

bool C_Smog::Update(void)
{
	//移動
	judg.SetTransMat(&smog.Base.Trans, &smog.Base.TraPos);
	smog.Base.Mat = smog.Base.Trans*smog.Base.Mat;

	return CountUpdate();
}

bool C_Smog::CountUpdate(void)
{
	//一秒減らす
	NowCount -= 1;
	if (NowCount <= 0) {
		//時間が経った
		NowCount = 0;
		return false;
	}
	return true;
}

void C_Smog::Draw3D(D3DXVECTOR3 CamPos)
{
	MoveVecJudg();

	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ

	Update_Alpha();
	for (int v = 0; v < 4; v++) {
		smog.v[v].Color = D3DCOLOR_ARGB(M_S_Smog.Alpha, 255, 255, 255);
	}
	lpD3DDevice->SetTexture(0, smog.TEX.Tex);
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);

	smog.Base.Pos = judg.SetPosM(smog.Base.Mat);

	//ビルボード
	D3DXVECTOR3 vec, oPos, nPos;
	vec = D3DXVECTOR3(0.0f, GetPolSize(), 0.0f);
	nPos = smog.Base.Pos + vec;
	oPos = smog.Base.Pos - vec;
	vec = judg.Billboard(oPos, nPos, CamPos, vec.y);
	smog.v[0].Pos = nPos - vec;
	smog.v[1].Pos = nPos + vec;
	smog.v[2].Pos = oPos + vec;
	smog.v[3].Pos = oPos - vec;
	int num=M_S_Smog.Draw_No;
	smog.v[0].Tex = D3DXVECTOR2(32.0f*(num % 8) / 256.0f, 32.0f*(num / 8) / 256.0f);
	smog.v[1].Tex = D3DXVECTOR2(32.0f*(num % 8 + 1) / 256.0f, 32.0f*(num / 8) / 256.0f);
	smog.v[2].Tex = D3DXVECTOR2(32.0f*(num % 8 + 1) / 256.0f, 32.0f*(num / 8 + 1) / 256.0f);
	smog.v[3].Tex = D3DXVECTOR2(32.0f*(num % 8) / 256.0f, 32.0f*(num / 8 + 1) / 256.0f);
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, smog.v, sizeof(VERTEX));//2はポリゴン数

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void C_Smog::Init_Num(void)
{
	M_S_Smog.Draw_No = 47;//薄い４７、濃い３５
	//濃い47,薄い53
}

void C_Smog::NumJudg(void)
{
	if (M_S_Smog.Draw_No < 0)M_S_Smog.Draw_No = 0;
	if (M_S_Smog.Draw_No > 63)M_S_Smog.Draw_No = 63;
}

void C_Smog::SetNum(const int s_Num)
{
	M_S_Smog.Draw_No = s_Num;
	NumJudg();
}

void C_Smog::Init_Mat(void)
{

	//回転
	D3DXMATRIX l_RotYMat;
	D3DXMatrixRotationY(&l_RotYMat, D3DXToRadian(180.0f));
	smog.Base.Mat = l_RotYMat * smog.Base.Mat;

	//
	MoveVecFlg = false;

	//移動ベクトルの初期化
	smog.Base.TraPos =judg.GetVecVec_S(&M_S_Smog.MoveVec,&M_S_Smog.Frame);
	
	//移動で分散させる
	D3DXVECTOR3 L_RandPos = D3DXVECTOR3(RandPlus(&M_S_Smog.Random.x), RandPlus(&M_S_Smog.Random.y), RandPlus(&M_S_Smog.Random.z));
	smog.Base.TraPos += judg.GetVecVec_S(&L_RandPos,&M_S_Smog.Frame) / 10.0f;
	

	smog.Base.TraPos *= 0.5f;

	//時限の初期化
	NowCount = 1*1000;

	M_S_Smog.AStart = NowCount;

}

void C_Smog::Update_Alpha(void)
{
	if (NowCount < M_S_Smog.AStart) M_S_Smog.Alpha -= M_S_Smog.AUp;
	if (M_S_Smog.Alpha < 0)M_S_Smog.Alpha = NowCount = 0;
}

float C_Smog::RandPlus(const int * Num)
{
	if (*Num <= 0)return 0.0f;
	
	int x = rand() % (*Num);
	if (rand() % 2 < 1)x *= -1;
	return (float)x;
}

float C_Smog::GetPolSize(void)
{
	M_S_Smog.PolBit += M_S_Smog.PolBitUp;
	if (M_S_Smog.PolBit > 1.0f)M_S_Smog.PolBit = 1.0f;
	float f=M_S_Smog.PolSize*M_S_Smog.PolBit;
	return f;
}

void C_Smog::PosMoveVec(const D3DXVECTOR3 * MoveVec)
{
	if (MoveVecJudg() != true)return;

	judg.VecMatIn(&smog.Base.Mat, *MoveVec);

	return;
}

bool C_Smog::MoveVecJudg(void)
{
	if (MoveVecFlg == false) {
		MoveVecFlg = true;
		return false;
	}
	return true;
}
