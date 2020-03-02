#include "Draw_3D_Mesh_1.h"

extern XfileManager xfileManager;

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス

void DrawMesh(XFILE *XFile);

C_Draw_3D_Mesh_1::C_Draw_3D_Mesh_1(std::string FileName)
{
	M_Mesh.Mesh = xfileManager.GetXfile(FileName);
}

void C_Draw_3D_Mesh_1::Draw(const D3DXVECTOR3 * CameraPos, const D3DXMATRIX * Mat)
{
	if (M_Mesh.Mesh.lpMesh == nullptr)return;

	lpD3DDevice->SetTransform(D3DTS_WORLD, Mat);
	DrawMesh(&M_Mesh.Mesh);
}
