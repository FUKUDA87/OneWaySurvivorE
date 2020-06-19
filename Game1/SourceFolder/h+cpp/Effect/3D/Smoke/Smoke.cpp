#include "Smoke.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../GameSource/Judgment.h"

extern LPDIRECT3DDEVICE9	lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

c_Smoke::c_Smoke(const D3DXMATRIX * Mat, const S_Smog * H_Smog, const float * HpPer, const int * NowHp)
{
	smog.TEX = { NULL,256,256,NULL,NULL,NULL };
	smog.TEX.Tex = textureManager.GetTexture("Smoke.png", smog.TEX.Width, smog.TEX.Height, NULL);
	//ŽžŒÀ‚Ì‰Šú‰»
	NowCount = 1;

	ScalSize = 0.0f;

	smog.Base.Mat = *Mat;

	M_S_Smog = *H_Smog;

	// ‰Œ‚Ì”Z‚³‚Ì‰Šú‰»
	Draw_No = InitDrawNo(HpPer, NowHp);

	//‰ñ“]
	D3DXMATRIX l_RotYMat;
	D3DXMatrixRotationY(&l_RotYMat, D3DXToRadian(180.0f));
	smog.Base.Mat = l_RotYMat * smog.Base.Mat;

	//ˆÚ“®ƒxƒNƒgƒ‹‚Ì‰Šú‰»
	Judg judg;
	smog.Base.TraPos = judg.GetVecVec_S(&M_S_Smog.MoveVec, &M_S_Smog.Frame);

	//ˆÚ“®‚Å•ªŽU‚³‚¹‚é
	D3DXVECTOR3 L_RandPos = D3DXVECTOR3(RandPlus(&M_S_Smog.Random.x), RandPlus(&M_S_Smog.Random.y), RandPlus(&M_S_Smog.Random.z));
	smog.Base.TraPos += judg.GetVecVec_S(&L_RandPos, &M_S_Smog.Frame) / 10.0f;


	smog.Base.TraPos *= 0.5f;

	//ŽžŒÀ‚Ì‰Šú‰»
	NowCount = 1 * 1000;

	M_S_Smog.AStart = NowCount;
}

bool c_Smoke::Update(const s_CarEffectUpdateData * updateData)
{
	//ˆÚ“®
	Judg judg;
	judg.Set_TransMat(&smog.Base.Trans, &smog.Base.TraPos);
	smog.Base.Mat = smog.Base.Trans*smog.Base.Mat;

	judg.VecMatIn(&smog.Base.Mat, updateData->MoveVec);
	

	return CountUpdate();
}

void c_Smoke::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//ƒoƒO

	Update_Alpha();
	for (int v = 0; v < 4; v++) {
		smog.v[v].Color = D3DCOLOR_ARGB(M_S_Smog.Alpha, 255, 255, 255);
	}
	lpD3DDevice->SetTexture(0, smog.TEX.Tex);
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);

	Judg judg;
	judg.SetPosM(&smog.Base.Pos, &smog.Base.Mat);

	//ƒrƒ‹ƒ{[ƒh
	D3DXVECTOR3 vec, oPos, nPos;
	vec = D3DXVECTOR3(0.0f, GetPolSize(), 0.0f);
	nPos = smog.Base.Pos + vec;
	oPos = smog.Base.Pos - vec;
	vec = judg.Billboard(&oPos, &nPos, CameraPos, &vec.y);
	smog.v[0].Pos = nPos - vec;
	smog.v[1].Pos = nPos + vec;
	smog.v[2].Pos = oPos + vec;
	smog.v[3].Pos = oPos - vec;
	int num = Draw_No;
	smog.v[0].Tex = D3DXVECTOR2(32.0f*(num % 8) / 256.0f, 32.0f*(num / 8) / 256.0f);
	smog.v[1].Tex = D3DXVECTOR2(32.0f*(num % 8 + 1) / 256.0f, 32.0f*(num / 8) / 256.0f);
	smog.v[2].Tex = D3DXVECTOR2(32.0f*(num % 8 + 1) / 256.0f, 32.0f*(num / 8 + 1) / 256.0f);
	smog.v[3].Tex = D3DXVECTOR2(32.0f*(num % 8) / 256.0f, 32.0f*(num / 8 + 1) / 256.0f);
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, smog.v, sizeof(VERTEX));//2‚Íƒ|ƒŠƒSƒ“”

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

bool c_Smoke::CountUpdate(void)
{
	//ˆê•bŒ¸‚ç‚·
	NowCount -= 1;
	if (NowCount <= 0) {
		//ŽžŠÔ‚ªŒo‚Á‚½
		NowCount = 0;
		return false;
	}
	return true;
}

int c_Smoke::InitDrawNo(const float * HpPer, const int * NowHp)
{
	if (*NowHp <= 0)return 35;
	if (*HpPer < 0.1f)return 47;
	if (*HpPer < 0.2f)return 50;
	if (*HpPer < 0.3f)return 53;
	
	return 0;

	//”–‚¢‚S‚VA”Z‚¢‚R‚T
	//”Z‚¢47,”–‚¢53
}

void c_Smoke::Update_Alpha(void)
{
	if (NowCount < M_S_Smog.AStart) M_S_Smog.Alpha -= M_S_Smog.AUp;
	if (M_S_Smog.Alpha < 0)M_S_Smog.Alpha = NowCount = 0;
}

float c_Smoke::RandPlus(const int * Num)
{
	if (*Num <= 0)return 0.0f;

	int x = rand() % (*Num);
	if (rand() % 2 < 1)x *= -1;
	return (float)x;
}

float c_Smoke::GetPolSize(void)
{
	M_S_Smog.PolBit += M_S_Smog.PolBitUp;
	if (M_S_Smog.PolBit > 1.0f)M_S_Smog.PolBit = 1.0f;
	float f = M_S_Smog.PolSize*M_S_Smog.PolBit;
	return f;
}