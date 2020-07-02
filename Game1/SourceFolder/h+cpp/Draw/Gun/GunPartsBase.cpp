#include "GunPartsBase.h"

extern LPDIRECT3DDEVICE9 lpD3DDevice;

void DrawMesh(XFILE *XFile);

bool c_GunPartsBase::Update(const D3DXMATRIX * BaseMat, const bool * ShotFlg)
{
	mat = *BaseMat;

	return true;
}

void c_GunPartsBase::Draw3D(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}
