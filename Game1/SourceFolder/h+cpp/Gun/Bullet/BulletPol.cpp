#include "BulletPol.h"

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_BulletPol::C_BulletPol(const GETGUNDATA * GetGunData):C_BulletDraw3DBase(GetGunData)
{
	BPolNum = GetGunData->PolNum;
	PolMat = new D3DXMATRIX[BPolNum];
	BPolSize = GetGunData->PolSize;
	MoveFlg = false;
	SetTex(&GetGunData->TexNo);
	Bullet.Mat= GetGunData->Mat;
	for (int b = 0; b < BPolNum; b++) {
		PolMat[b] = Bullet.Mat;
	}
}

C_BulletPol::~C_BulletPol()
{
	if (PolMat != nullptr) {
		delete[] PolMat;
	}
}

bool C_BulletPol::Update(void)
{
	for (int b = BPolNum-1; b >0; b--) {
		PolMat[b] = PolMat[b-1];
	}
	D3DXMATRIX Tmp;
	D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, Speed);
	Bullet.Mat = Tmp * Bullet.Mat;
	PolMat[0] = Bullet.Mat;
	return CountUpdate();
}

bool C_BulletPol::UpdateSet(const D3DXVECTOR3 * mVec)
{
	D3DXVECTOR3 Vec = *mVec;
	if (MoveFlg == false) {
		MoveFlg = true;
	}
	else {
		//位置補正
		judg.VecMatIn(&Bullet.Mat, Vec);
		if (PolMat != nullptr) {
			for (int i = 0; i < BPolNum; i++) {
				judg.VecMatIn(&PolMat[i], Vec);
			}
		}
	}
	return true;
}

void C_BulletPol::Draw3DAll(const D3DXVECTOR3 * CamPos)
{
	Draw3DPol(CamPos);
}

void C_BulletPol::Draw3DPol(const D3DXVECTOR3 *CamPos)
{
	if (MoveFlg == false) {
		MoveFlg = true;
	}
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	lpD3DDevice->SetTexture(0, BTex.Tex);
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);
	for (int i = 0; i < (BPolNum - 1); i++) {
		//ビルボード
		D3DXVECTOR3 vec, oPos, nPos;
		judg.SetPosM(&nPos, PolMat[i]);
		judg.SetPosM(&oPos, PolMat[i + 1]);
		vec = judg.Billboard(oPos, nPos, *CamPos, BPolSize);
		v[0].Pos = nPos - vec;
		v[1].Pos = nPos + vec;
		v[2].Pos = oPos + vec;
		v[3].Pos = oPos - vec;
		v[0].Tex = D3DXVECTOR2(0.0f, (float)i / (float)(BPolNum - 1));
		v[1].Tex = D3DXVECTOR2(1.0f, (float)i / (float)(BPolNum - 1));
		v[2].Tex = D3DXVECTOR2(1.0f, (float)(i + 1) / (float)(BPolNum - 1));
		v[3].Tex = D3DXVECTOR2(0.0f, (float)(i + 1) / (float)(BPolNum - 1));
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));//2はポリゴン数
	}
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void C_BulletPol::SetTex(const int * TexNo)
{
	C_BulletTexManager bulletTexManager;
	BTex.Tex = bulletTexManager.GetTex(*TexNo);
}
