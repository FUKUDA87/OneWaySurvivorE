#include "Draw_Mesh_Base_A.h"
#include"../../GameSource/XfileManager.h"

extern XfileManager xfileManager;

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス

void DrawMesh(XFILE *XFile);

C_Draw_Mesh_Base::C_Draw_Mesh_Base()
{
	Init_Mesh();
}

C_Draw_Mesh_Base::C_Draw_Mesh_Base(std::string FileName)
{
	M_Mesh = xfileManager.GetXfile(FileName);
	Init_Mesh();
}

void C_Draw_Mesh_Base::Draw3D(const D3DXVECTOR3 * CameraPos)
{

	Mesh_Draw_No1();
}

void C_Draw_Mesh_Base::Set_MoveVec(const D3DXVECTOR3 * MoveVec)
{

}

LPD3DXMESH C_Draw_Mesh_Base::Get_Mesh(void)
{
	return M_Mesh.lpMesh;
}

D3DXVECTOR3 C_Draw_Mesh_Base::Get_Pol_Pos(const int * PosNo)
{
	return D3DXVECTOR3();
}

////////////////////////////////////////////////////////////////

void C_Draw_Mesh_Base::Init_Mesh(void)
{
	Draw_JudgFlg = Co_Draw_Mesh;
}

void C_Draw_Mesh_Base::Mesh_Draw_No1(void)
{
	if (M_Mesh.lpMesh == nullptr)return;

	lpD3DDevice->SetTransform(D3DTS_WORLD, &Get_DrawMat());
	DrawMesh(&M_Mesh);
}

void C_Draw_Mesh_Base::Mesh_Load(std::string FileName)
{
	M_Mesh = xfileManager.GetXfile(FileName);
}




