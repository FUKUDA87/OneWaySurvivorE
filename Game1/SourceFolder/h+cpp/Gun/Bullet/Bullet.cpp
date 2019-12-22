#include"Bullet.h"
#include"../../GameSource/TextureManager.h"
#include"../../GameSource/Judgment.h"

extern Judg judg;
extern TextureManager textureManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

Bullet::Bullet() {
	Init();
}
void Bullet::Init()
{
	bul.TEX = { NULL,32,16,0,0,0 };
	bul.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/bullet.png", bul.TEX.Width, bul.TEX.Height, NULL);
	D3DXMatrixIdentity(&IdenMat);
}
Bullet::Bullet(D3DXMATRIX mat) {
	Init();
	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, 0, 0, 1);
	bul.Base.Mat = TmpMat * mat;
	for (int i = 0; i < GNUM; i++) {
		smokeMat[i] = bul.Base.Mat;
	}
}
Bullet::Bullet(D3DXMATRIX mat, D3DXVECTOR3 pos)
{
	Init();
	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, 0, 0, 1);
	bul.Base.Mat = TmpMat * mat;
	//’e‚ªÆ€‚Ì•û‚ÉŒü‚©‚¤ˆ—
	double Ang,ang=0.0f;
	judg.CroDot(bul.Base.Mat, &bul.Base.Rot,pos, D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Ang,ang, false);
	bul.Base.Mat = bul.Base.Rot* bul.Base.Mat;
	for (int i = 0; i < GNUM; i++) {
		smokeMat[i] = bul.Base.Mat;
	}
}
Bullet::~Bullet() {

}
void Bullet::Draw(void) {

	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//ƒoƒO
	bul.v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	bul.v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	bul.v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	bul.v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	lpD3DDevice->SetTexture(0, bul.TEX.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);
	float f = 0.05f;
	for (int i = 0; i < (GNUM-1); i++) {
		D3DXVec3TransformCoord(&bul.v[0].Pos, &D3DXVECTOR3(-f, 0, 0), &smokeMat[i]);
		D3DXVec3TransformCoord(&bul.v[1].Pos, &D3DXVECTOR3(f, 0, 0), &smokeMat[i]);
		D3DXVec3TransformCoord(&bul.v[2].Pos, &D3DXVECTOR3(f, 0, 0), &smokeMat[i + 1]);
		D3DXVec3TransformCoord(&bul.v[3].Pos, &D3DXVECTOR3(-f, 0, 0), &smokeMat[i + 1]);
		bul.v[0].Tex = D3DXVECTOR2((float)1 / 2.0f, (float)i / (float)(GNUM-1));
		bul.v[1].Tex = D3DXVECTOR2((float)1/1.0f, (float)i / (float)(GNUM - 1));
		bul.v[2].Tex = D3DXVECTOR2((float)1 / 1.0f, (float)(i + 1) / (float)(GNUM - 1));
		bul.v[3].Tex = D3DXVECTOR2((float)1 / 2.0f, (float)(i + 1) / (float)(GNUM - 1));
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, bul.v, sizeof(VERTEX));//2‚Íƒ|ƒŠƒSƒ“”
	}
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	
}
bool Bullet::Update(void) {
	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, 0, 0, 1);
	bul.Base.Mat = TmpMat * bul.Base.Mat;
	for (int i = (GNUM - 1); i > 0; i--) {
		smokeMat[i] = smokeMat[i - 1];
	}
	smokeMat[0] = bul.Base.Mat;
	return true;
}

bool Bullet::UpdateM(D3DXVECTOR3 bVec)
{
	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, 0, 0, 1);
	bul.Base.Mat = TmpMat * bul.Base.Mat;
	for (int i = (GNUM - 1); i > 0; i--) {
		smokeMat[i] = smokeMat[i - 1];
	}
	smokeMat[0] = bul.Base.Mat;
	/*judg.VecMatIn(&bul.Base.Mat, mVec);
	for (int i = 0; i < GNUM; i++) {
		judg.VecMatIn(&smokeMat[1], mVec);
	}*/
	return true;
}
