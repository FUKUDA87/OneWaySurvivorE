#include"XFileManager.h"

void LoadMesh(struct XFILE *XFile, const char FName[]);
void ReleaseMesh(struct XFILE *XFile);
extern LPDIRECT3DDEVICE9 lpD3DDevice;

XFileManager::~XFileManager() {
	AllDelete();
}
XFILE XFileManager::GetMesh(std::string FileName)
{
	XFILE *Mesh;
	if (xfileList.find(FileName) == xfileList.end()) {
		Mesh = new XFILE;
		char FileName2[100];
		sprintf_s(FileName2, sizeof(FileName2), "../GameFolder/Material/XFile/%s", &FileName[0]);
		LoadMesh(Mesh, FileName2);
		LPD3DXMESH TmpMesh;
		Mesh->lpMesh->CloneMeshFVF(D3DXMESH_NPATCHES | D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, lpD3DDevice, &TmpMesh);
		Mesh->lpMesh->Release();
		Mesh->lpMesh = TmpMesh;
		xfileList[FileName] = Mesh;
	}
	else {
		Mesh = xfileList[FileName];
	}
	return *Mesh;
}
void XFileManager::AllDelete(void) {
	for (auto itr = xfileList.begin(); itr != xfileList.end(); itr++) {
		ReleaseMesh(itr->second);
		delete itr->second;
	}
	xfileList.clear();
}