#include "BulletEA.h"

void BulletEA::InitE()
{
	bul.TEX = { NULL,64,64,0,0,0 };
	bul.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/Bullet1TG.png", bul.TEX.Width, bul.TEX.Height, NULL);
	MoveSize = 1.1f;
	bul.Base.TraPos = D3DXVECTOR3(0.0f, 0.0f, MoveSize);//弾のスピード
	D3DXMatrixTranslation(&bul.Base.Trans, bul.Base.TraPos.x, bul.Base.TraPos.y, bul.Base.TraPos.z);
}

void BulletEA::Draw3D()
{
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	bul.v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	bul.v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	bul.v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	bul.v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	lpD3DDevice->SetTexture(0, bul.TEX.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);
	for (int i = 0; i < (GNUM - 1); i++) {
		//ビルボード
		D3DXVECTOR3 vec, oPos, nPos;
		judg.SetPosM(&nPos, smokeMat[i]);
		judg.SetPosM(&oPos, smokeMat[i + 1]);
		vec = judg.Billboard(oPos, nPos, inv.GetcaPos(), 0.07f);
		bul.v[0].Pos = nPos - vec;
		bul.v[1].Pos = nPos + vec;
		bul.v[2].Pos = oPos + vec;
		bul.v[3].Pos = oPos - vec;
		bul.v[0].Tex = D3DXVECTOR2(0.0f, (float)i / (float)(GNUM - 1));
		bul.v[1].Tex = D3DXVECTOR2((float)1, (float)i / (float)(GNUM - 1));
		bul.v[2].Tex = D3DXVECTOR2((float)1, (float)(i + 1) / (float)(GNUM - 1));
		bul.v[3].Tex = D3DXVECTOR2(0.0f, (float)(i + 1) / (float)(GNUM - 1));
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, bul.v, sizeof(VERTEX));//2はポリゴン数
	}
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
