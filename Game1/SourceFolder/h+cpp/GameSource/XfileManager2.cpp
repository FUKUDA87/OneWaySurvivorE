#include "XfileManager2.h"
#include"Judgment.h"

void LoadMesh(struct XFILE *XFile, const char FName[]);
void ReleaseMesh(struct XFILE *XFile);
extern LPDIRECT3DDEVICE9 lpD3DDevice;

XfileManager2::~XfileManager2()
{
	AllDelete();
}

XFILE_B XfileManager2::GetXfile(std::string FileName)
{
	XFILE_B Xfile;
	if (xfileList.find(FileName) == xfileList.end()) {
		char FileName2[100];
		sprintf_s(FileName2, sizeof(FileName2), "../GameFolder/Material/XFile/%s", &FileName[0]);
		LoadMesh(&Xfile.Mesh, FileName2);

		LPD3DXMESH TmpMesh;
		Xfile.Mesh.lpMesh->CloneMeshFVF(D3DXMESH_NPATCHES | D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, lpD3DDevice, &TmpMesh);
		//座標         法線           テクスチャ座標              クローン
		Xfile.Mesh.lpMesh->Release();
		Xfile.Mesh.lpMesh = TmpMesh;

		Xfile.Data.NumVertex = Xfile.Mesh.lpMesh->GetNumVertices();

		CLONEVERTEX *pV;
		D3DXVECTOR3 BigPos , SmallPos;
		Xfile.Mesh.lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);

		Judg judg;
		for (DWORD No = 0; No < Xfile.Data.NumVertex; No++) {
			if (No > 0) {
				judg.Pos_Big_Judg(&BigPos, &(pV + No)->Pos);
				judg.Pos_Small_Judg(&SmallPos, &(pV + No)->Pos);
			}
			else {
				BigPos = SmallPos = (pV + No)->Pos;
			}
		}



		Xfile.Data.Pos_Big = BigPos;
		Xfile.Data.Pos_Small = SmallPos;

		Xfile.Mesh.lpMesh->UnlockVertexBuffer();

		xfileList[FileName] = Xfile;
	}
	else {
		Xfile = xfileList[FileName];
	}
	return Xfile;
}

void XfileManager2::AllDelete(void)
{
	for (auto itr = xfileList.begin(); itr != xfileList.end(); itr++) {
		ReleaseMesh(&(itr->second.Mesh));
		//delete (itr->second);
	}
	xfileList.clear();
}
