#include "Spear.h"

void Spear::Init()
{
	xfileManager.GetXfile(&s.Mesh, "../GameFolder/Material/XFile/spear.x");
	e.Mesh = s.Mesh;
	s.Base.DrawFlg = true;
	e.Base.DrawFlg = true;
	xfileManager.GetXfile(&v.Mesh, "../GameFolder/Material/XFile/Vector1.x");
}

Spear::Spear(D3DXMATRIX TmpStart, D3DXMATRIX TmpEnd)
{
	Init();
	s.Base.Trans = TmpStart;
	e.Base.Trans = TmpEnd;
}

void Spear::Update(D3DXMATRIX Mat, bool DrawFlg)
{
	s.Base.Mat = s.Base.Trans*Mat;
	e.Base.Mat = e.Base.Trans*Mat;
	s.Base.DrawFlg = DrawFlg;
	e.Base.DrawFlg = DrawFlg;
}

void Spear::Draw3D(void)
{
	if (s.Base.DrawFlg == true) {
		lpD3DDevice->SetTransform(D3DTS_WORLD, &s.Base.Mat);
		DrawMesh(&s.Mesh);
	}
	if (e.Base.DrawFlg == true) {
		lpD3DDevice->SetTransform(D3DTS_WORLD, &e.Base.Mat);
		DrawMesh(&e.Mesh);
	}
}

void Spear::Draw3D(D3DXMATRIX Mat)
{
	s.Base.Mat = Mat;
	lpD3DDevice->SetTransform(D3DTS_WORLD, &s.Base.Mat);
	DrawMesh(&s.Mesh);
}

void Spear::Draw3DV(D3DXMATRIX Mat)
{
	v.Base.Mat = Mat;
	lpD3DDevice->SetTransform(D3DTS_WORLD, &v.Base.Mat);
	DrawMesh(&v.Mesh);
}
