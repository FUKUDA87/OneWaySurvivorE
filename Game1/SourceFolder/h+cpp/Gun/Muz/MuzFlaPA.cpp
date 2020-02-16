#include "MuzFlaPA.h"

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

void MuzFlaPA::Init()
{
	mf.Base.Flg = true;
	mf.TEX = { NULL,128,128,NULL,NULL,NULL };
	mf.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/MuzFla1T.png", mf.TEX.Width, mf.TEX.Height, NULL);
	//Z‰ñ“]
	D3DXMatrixRotationZ(&mf.Base.RotZ, D3DXToRadian((float)(rand() % 360)));
}

MuzFlaPA::MuzFlaPA(D3DXMATRIX Mat, D3DXMATRIX Tmp)
{
	Init();
	mf.Base.Mat = mf.Base.RotZ*Tmp * Mat;
}

void MuzFlaPA::Draw3D()
{
	if (mf.Base.Flg == true) {
		lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		lpD3DDevice->SetTexture(0, mf.TEX.Tex);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &mf.Base.Mat);
		lpD3DDevice->SetFVF(FVF_VERTEX);//ƒoƒO
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, mf.v, sizeof(VERTEX));//2‚Íƒ|ƒŠƒSƒ“”
		lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		mf.Base.Flg = false;
	}
}

bool MuzFlaPA::Update()
{
	D3DXVECTOR3 Pos(0.25f, 0.25f, 0.0f);
	mf.v[0].Pos = D3DXVECTOR3(-Pos.x, Pos.y, 0.0f);//x,y,z
	mf.v[1].Pos = D3DXVECTOR3(Pos.x, Pos.y, 0.0f);
	mf.v[2].Pos = D3DXVECTOR3(Pos.x, -Pos.y, 0.0f);
	mf.v[3].Pos = D3DXVECTOR3(-Pos.x, -Pos.y, 0.0f);

	mf.v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	mf.v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	mf.v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	mf.v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	mf.v[0].Tex = D3DXVECTOR2(0.0f,0.0f);
	mf.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	mf.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	mf.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);
	return mf.Base.Flg;
}
