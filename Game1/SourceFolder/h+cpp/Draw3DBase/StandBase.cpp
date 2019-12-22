#include"StandBase.h"
#include"../GameSource/XfileManager.h"
#include"../GameSource/Judgment.h"


extern Judg judg;
extern XfileManager xfileManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;

void DrawMesh(XFILE *XFile);

//Stand1::Stand1() {
//	//y = 0.75f;
//	//z = -0.2f;//-0.4
//	//xfileManager.GetXfile(&standMesh, "../GameFolder/Material/XFile/stand1.x");
//	//D3DXMatrixTranslation(&standMat, Car.Base.Mat._41, Car.Base.Mat._42+y, Car.Base.Mat._43+z);
//}
//Stand1::~Stand1() {
//	
//}
//bool Stand1::UpdateSta()
//{
//	return false;
//}
//void Stand1::Draw3DSta()
//{
//}
//D3DXMATRIX Stand1::GetDrawMatSta(void)
//{
//	judg.ScalingMat(&Stand.Scal, &Stand.ScaPos);
//	return Stand.Scal*Stand.Mat;
//}
//bool Stand1::SUpdate(void) {
//	//D3DXMatrixTranslation(&standMat, player.Base.Mat._41, player.Base.Mat._42 + y, player.Base.Mat._43+z);
//	D3DXMATRIX tmp;
//	D3DXMatrixTranslation(&tmp,0.0f, y,z);
//	standMat = tmp * Car.Base.Mat;
//
//	return true;
//}
//void Stand1::SDraw(void) {
//	lpD3DDevice->SetTransform(D3DTS_WORLD, &standMat);
//	DrawMesh(&standMesh);
//}

C_StandBase::C_StandBase()
{
	InitStand();
}

C_StandBase::~C_StandBase()
{
}

void C_StandBase::InitStand(void)
{
	judg.InitMatPos(&Stand.Mat, &Stand.TraPos, &Stand.ScaPos);
	SetMeshSta(1);
}

bool C_StandBase::UpdateSta()
{
	return true;
}

void C_StandBase::Draw3DSta()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &GetDrawMatSta());
	DrawMesh(&StandMesh);
}

D3DXMATRIX C_StandBase::GetDrawMatSta(void)
{
	judg.ScalingMat(&Stand.Scal, &Stand.ScaPos);
	return Stand.Scal*Stand.Mat;
}

void C_StandBase::SetMeshSta(int MeshNo)
{
	StandMesh = standMeshManager.GetMesh(MeshNo);
}
