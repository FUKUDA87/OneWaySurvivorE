#include"XfileManager.h"

void LoadMesh(struct XFILE *XFile, const char FName[]);
void ReleaseMesh(struct XFILE *XFile);
extern LPDIRECT3DDEVICE9 lpD3DDevice;


void XfileManager::GetXfile(XFILE *x,std::string FileName) {
	if (xfileList.find(FileName) == xfileList.end()) {
		LoadMesh(x, &FileName[0]);
		xfileList[FileName] = *x;
	}
	else {
		*x = xfileList[FileName];
	}
	return;
}
XfileManager::~XfileManager() {
	AllDelete();
}
XFILE XfileManager::GetXfile(std::string FileName)
{
	XFILE Mesh;
	if (xfileList.find(FileName) == xfileList.end()) {
		LoadMesh(&Mesh, &FileName[0]);
		/*LPD3DXMESH TmpMesh;
		x->lpMesh->CloneMeshFVF(D3DXMESH_NPATCHES | D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, lpD3DDevice, &TmpMesh);
																		   座標         法線           テクスチャ座標              クローン
		x->lpMesh->Release();
		x->lpMesh = TmpMesh;*/
		xfileList[FileName] = Mesh;
	}
		else {
		Mesh = xfileList[FileName];
	}
	return Mesh;
}
void XfileManager::AllDelete(void) {
	for (auto itr = xfileList.begin(); itr != xfileList.end(); itr++) {
		ReleaseMesh(&(itr->second));
		//delete (itr->second);
	}
	xfileList.clear();
}