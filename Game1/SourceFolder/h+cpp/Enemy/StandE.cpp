#include "StandE.h"
#include"../GameSource/XfileManager.h"

extern XfileManager xfileManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;

void DrawMesh(XFILE *XFile);

void StandE::InitSta()
{
	Pos = D3DXVECTOR3(0.0f, 0.7f, -0.15f);
	xfileManager.GetXfile(&stand.Mesh, "../GameFolder/Material/XFile/stand2e.x");
	D3DXMatrixTranslation(&stand.Base.Trans, Pos.x, Pos.y,Pos.z);
	stand.Base.Mat = stand.Base.Trans;
}

bool StandE::StaUpdate()
{
	stand.Base.Mat = stand.Base.Trans*enemy.CH.Base.Mat;
	return true;
}

void StandE::StaDraw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &stand.Base.Mat);
	DrawMesh(&stand.Mesh);
}

bool StandE::UpdateAll()
{
	EneUpdate();
	TiUpdate();
	StaUpdate();
	return true;
}

void StandE::DrawAll()
{
	EneDraw();
	TiDraw();
	StaDraw();
	return;
}
