#include "BulletHole3D.h"
#include"../../GameSource/TextureManager.h"

extern TextureManager textureManager;
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_BulHol3D::C_BulHol3D(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos, int TypeNo)
{
	InitHol3D();

	Hole.Base.Mat = *Mat;
	judg.SetMatP(&Hole.Base.Mat, *Pos);

	InitWall(TypeNo);
	InitGround(TypeNo);
}

C_BulHol3D::~C_BulHol3D()
{
}

void C_BulHol3D::InitHol3D(void)
{
	//画像のロード
	Hole.TEX = { NULL,300,300,NULL,NULL,NULL };
	Hole.TEX.Tex=textureManager.GetTexture("../GameFolder/Material/Texture/BulletBack1C.png", Hole.TEX.Width, Hole.TEX.Height, NULL);

	NowCount = 1 * 60;
}

bool C_BulHol3D::UpdateHol3D(void)
{
	for (int i = 0; i < 4; i++) {
		Hole.v[i].Color= D3DCOLOR_ARGB(255, 255, 255, 255);
	}
	Hole.v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	Hole.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	Hole.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	Hole.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	return CountUpdate();
}

void C_BulHol3D::Draw3DHol3D(void)
{
	//lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	
	lpD3DDevice->SetTexture(0, Hole.TEX.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &Hole.Base.Mat);
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Hole.v, sizeof(VERTEX));//2はポリゴン数

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

bool C_BulHol3D::CountUpdate(void)
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

void C_BulHol3D::InitWall(int TypeNo)
{
	if (TypeNo != 1)return;
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.05f, 0.05f);
	Hole.v[0].Pos = D3DXVECTOR3(Pos.x, Pos.y, -Pos.z);
	Hole.v[1].Pos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);
	Hole.v[2].Pos = D3DXVECTOR3(Pos.x, -Pos.y, Pos.z);
	Hole.v[3].Pos = D3DXVECTOR3(Pos.x, -Pos.y, -Pos.z);
}

void C_BulHol3D::InitGround(int TypeNo)
{
	if (TypeNo != 2)return;
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.05f, 0.0f, 0.05f);
	Hole.v[0].Pos = D3DXVECTOR3(-Pos.x, Pos.y, Pos.z);
	Hole.v[1].Pos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);
	Hole.v[2].Pos = D3DXVECTOR3(Pos.x, Pos.y, -Pos.z);
	Hole.v[3].Pos = D3DXVECTOR3(-Pos.x, Pos.y, -Pos.z);
}
