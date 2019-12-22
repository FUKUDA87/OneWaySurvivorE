#include "BulletPA.h"
#include"../../GameSource/InvBi.h"

extern Inv inv;

void BulletPA::Init()
{
	bul.TEX = { NULL,32,16,0,0,0 };
	bul.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/bulletG.png", bul.TEX.Width, bul.TEX.Height, NULL);
	D3DXMatrixIdentity(&IdenMat);
	GNUM = 4;
	smokeMat = new D3DXMATRIX[GNUM];
	MoveSize = 1.0f;
	bul.Base.TraPos = D3DXVECTOR3(0.0f, 0.0f, MoveSize);//弾のスピード
	MoBuFlg = false;
	D3DXMatrixTranslation(&bul.Base.Trans, bul.Base.TraPos.x, bul.Base.TraPos.y, bul.Base.TraPos.z);
	//時間の初期化
	NowCount = 5 * 60;
}

BulletPA::BulletPA()
{
	Init();
}

BulletPA::BulletPA(D3DXMATRIX Mat,D3DXMATRIX GmMat, D3DXVECTOR3 Pos, bool PFlg)
{
	Init();
	bul.Base.Mat = GmMat * Mat;
	if (PFlg == true) {
		//弾が照準の方に向かう処理
		double Ang, ang = 0.0f;
		judg.CroDot(bul.Base.Mat, &bul.Base.Rot, Pos, D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Ang, ang, false);
		bul.Base.Mat = bul.Base.Rot* bul.Base.Mat;
	}
	for (int i = 0; i < GNUM; i++) {
		smokeMat[i] = bul.Base.Mat;
	}
	
}

BulletPA::~BulletPA()
{
	if (smokeMat != nullptr) {
		delete[] smokeMat;
	}
}

void BulletPA::Draw3D()
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
		vec=judg.Billboard(oPos, nPos, inv.GetcaPos(), 0.05f);	
		bul.v[0].Pos = nPos - vec;
		bul.v[1].Pos = nPos + vec;
		bul.v[2].Pos = oPos + vec;
		bul.v[3].Pos = oPos - vec;
		bul.v[0].Tex = D3DXVECTOR2((float)1 / 2.0f, (float)i / (float)(GNUM - 1));
		bul.v[1].Tex = D3DXVECTOR2((float)1 / 1.0f, (float)i / (float)(GNUM - 1));
		bul.v[2].Tex = D3DXVECTOR2((float)1 / 1.0f, (float)(i + 1) / (float)(GNUM - 1));
		bul.v[3].Tex = D3DXVECTOR2((float)1 / 2.0f, (float)(i + 1) / (float)(GNUM - 1));
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, bul.v, sizeof(VERTEX));//2はポリゴン数
	}
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

bool BulletPA::Update()
{
	D3DXMatrixTranslation(&bul.Base.Trans,bul.Base.TraPos.x, bul.Base.TraPos.y,bul.Base.TraPos.z);
	bul.Base.Mat = bul.Base.Trans * bul.Base.Mat;
	for (int i = (GNUM - 1); i > 0; i--) {
		smokeMat[i] = smokeMat[i - 1];
	}
	smokeMat[0] = bul.Base.Mat;
	return UpdateTime();
}

bool BulletPA::UpdateMove(D3DXVECTOR3 bVec)
{
	if (MoBuFlg==true) {
		judg.VecMatIn(&bul.Base.Mat, bVec);
		for (int i = 0; i < GNUM; i++) {
			judg.VecMatIn(&smokeMat[i], bVec);
		}
	}
	else {
		MoBuFlg = true;
	}
	return true;
}
