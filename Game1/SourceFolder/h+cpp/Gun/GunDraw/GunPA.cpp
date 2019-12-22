#include "GunPA.h"
#include"../../GameSource/Judgment.h"

extern Judg judg;

void GunPA::Init()
{
	Pos=D3DXVECTOR3(0.0f,0.17f,0.0f);
	xfileManager.GetXfile(&gun.Mesh, "../GameFolder/Material/XFile/gun1.x");
	D3DXMatrixTranslation(&GmMat,0.0f,0.02f,0.75f);
}

GunPA::GunPA()
{
	Init();
}

GunPA::GunPA(D3DXMATRIX Mat)
{
	Init();
	D3DXMatrixTranslation(&gun.Base.Mat, Mat._41 + Pos.x, Mat._42 + Pos.y, Mat._43 + Pos.z);
	//Šg‘ås—ñ‚Ì‰Šú‰»
	gun.Base.ScaPos = D3DXVECTOR3(1.2f, 1.2f, 1.2f);
}

GunPA::~GunPA()
{
}

void GunPA::Draw3D()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &GetDrawMatGun());
	DrawMesh(&gun.Mesh);
}

bool GunPA::Update(float AngX, float AngY,D3DXMATRIX Mat)
{
	D3DXMatrixTranslation(&gun.Base.Trans, Pos.x+Mat._41, Pos.y + Mat._42, Pos.z + Mat._43);
	D3DXMatrixRotationX(&gun.Base.RotX, D3DXToRadian(AngX - 1));
	D3DXMatrixRotationY(&gun.Base.RotY, D3DXToRadian(AngY));
	gun.Base.Mat = gun.Base.RotX * gun.Base.RotY*gun.Base.Trans;
	return true;
}

bool GunPA::Update(const D3DXMATRIX * CamMat, D3DXMATRIX Mat)
{
	D3DXMatrixTranslation(&gun.Base.Trans, Pos.x + Mat._41, Pos.y + Mat._42, Pos.z + Mat._43);
	D3DXMatrixRotationX(&gun.Base.RotX, D3DXToRadian(- 1));
	gun.Base.Mat = gun.Base.RotX * *CamMat*gun.Base.Trans;
	return true;
}

bool GunPA::Update(D3DXMATRIX Mat)
{
	D3DXMatrixTranslation(&gun.Base.Trans, Pos.x, Pos.y, Pos.z);
	gun.Base.Mat = gun.Base.Trans*Mat;
	return true;
}
