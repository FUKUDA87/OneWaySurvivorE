#include "Smog.h"
#include"../GameSource/TextureManager.h"
#include"../GameSource/Judgment.h"
#include"../GameSource/InvBi.h"

extern Inv inv;

extern Judg judg;
extern LPDIRECT3DDEVICE9	lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_Smog::C_Smog(const D3DXVECTOR3 * Pos)
{
	Init();

	smog.Base.Pos = *Pos;
}

C_Smog::~C_Smog()
{
}

void C_Smog::Init()
{
	smog.TEX = { NULL,32,32,NULL,NULL,NULL };
	smog.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture//Smoke02.png", smog.TEX.Width, smog.TEX.Height, NULL);
	//時限の初期化
	NowCount = 1 * 10;

	D3DXMatrixIdentity(&smog.Base.Mat);

	yUp = 0.3f;

	ScalSize = 0.0f;
}

bool C_Smog::Update(void)
{
	smog.Base.Pos.y += yUp;
	ScalSize += 0.1f;
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

void C_Smog::Draw3D(void)
{
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ

	for (int c = 0; c < 4; c++) {
		smog.v[c].Color = D3DCOLOR_ARGB(100, 100, 100, 100);
	}
	lpD3DDevice->SetTexture(0, smog.TEX.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &smog.Base.Mat);
	//ビルボード
	D3DXVECTOR3 vec, oPos, nPos;
	vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	nPos = smog.Base.Pos + vec;
	oPos = smog.Base.Pos - vec;
	vec = judg.Billboard(oPos, nPos, inv.GetcaPos(), vec.z);
	smog.v[0].Pos = nPos - vec;
	smog.v[1].Pos = nPos + vec;
	smog.v[2].Pos = oPos + vec;
	smog.v[3].Pos = oPos - vec;
	smog.v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	smog.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	smog.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	smog.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, smog.v, sizeof(VERTEX));//2はポリゴン数

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void C_Smog::Draw3D(D3DXVECTOR3 CamPos)
{
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ

	smog.v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	smog.v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	smog.v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	smog.v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	lpD3DDevice->SetTexture(0, smog.TEX.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &smog.Base.Mat);
	//ビルボード
	D3DXVECTOR3 vec, oPos, nPos;
	vec = D3DXVECTOR3(0.0f, 1.0f*ScalSize, 0.0f);
	nPos = smog.Base.Pos + vec;
	oPos = smog.Base.Pos - vec;
	vec = judg.Billboard(oPos, nPos, CamPos, vec.y);
	smog.v[0].Pos = nPos - vec;
	smog.v[1].Pos = nPos + vec;
	smog.v[2].Pos = oPos + vec;
	smog.v[3].Pos = oPos - vec;
	smog.v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	smog.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	smog.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	smog.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, smog.v, sizeof(VERTEX));//2はポリゴン数

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
