#include "BulletMesh.h"
#include"../../GameSource/XfileManager.h"

extern XfileManager xfileManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス

void DrawMesh(XFILE *XFile);

C_BulletMesh::C_BulletMesh(const GETGUNDATA * GetGunData):C_BulletPol(GetGunData)
{
	Init(&GetGunData->MeshNo, &GetGunData->MeshScalPos);
}

void C_BulletMesh::Draw3DAll(const D3DXVECTOR3 * CamPos)
{
	Draw3DMesh();
	Draw3DPol(CamPos);
}

void C_BulletMesh::Draw3DMesh(void)
{
	if (BulletMesh.lpMesh == nullptr)return;

	D3DXMATRIX TmpMat;
	TmpMat = ScalMat * Bullet.Mat;
	lpD3DDevice->SetTransform(D3DTS_WORLD, &TmpMat);
	DrawMesh(&BulletMesh);
}

void C_BulletMesh::Init(const int *MeshNo, const D3DXVECTOR3 * ScalPos)
{
	BulletMesh = xfileManager.GetXfile("../GameFolder/Material/XFile/Missile.x");

	judg.ScalingMat(&ScalMat, ScalPos);
}
