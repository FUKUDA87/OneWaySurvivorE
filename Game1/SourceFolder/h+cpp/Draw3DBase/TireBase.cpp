#include "TireBase.h"

extern LPDIRECT3DDEVICE9 lpD3DDevice;

void DrawMesh(XFILE *XFile);


C_TireBase::C_TireBase()
{
	InitTire();
}

C_TireBase::C_TireBase(const BASE3D * TireBase)
{
	InitTire();
	Tire = *TireBase;
}

C_TireBase::~C_TireBase()
{
}

void C_TireBase::InitTire(void)
{
	SetMeshTire(1);
	//s—ñ‰Šú‰»
	judg.InitMatPos(&Tire.Mat, &Tire.TraPos, &Tire.ScaPos);
	//ƒtƒ‰ƒO‚Ì‰Šú‰»
	MoveTireFlg = false;
}

bool C_TireBase::UpdateTire(void)
{
	return true;
}

bool C_TireBase::UpdateTire(const D3DXMATRIX * CarMat)
{
	if (MoveTireFlg == true) {
		Tire.Mat = Tire.RotX *(*CarMat);
	}
	else {
		Tire.Mat = (*CarMat);
	}
	return false;
}

void C_TireBase::Draw3DTire(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &GetDrawMatTire());
	DrawMesh(&TireMesh);
}

void C_TireBase::SetMeshTire(int MeshNo)
{
	TireMesh = tireMeshManager.GetMesh(MeshNo);
}
