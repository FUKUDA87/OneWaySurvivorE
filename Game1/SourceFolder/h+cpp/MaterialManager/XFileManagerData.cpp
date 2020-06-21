#include "XFileManagerData.h"
#include"../GameSource/Judgment.h"
#include"XFileManager.h"

extern XFileManager xfileManager;

XFileManagerData::~XFileManagerData()
{
	AllDelete();
}

XFILE_B XFileManagerData::GetMesh(std::string FileName)
{
	XFILE_B Xfile;

	Xfile.Mesh = xfileManager.GetMesh(FileName);

	S_Mesh_Data *Data;

	if (MeshDataList.find(FileName) == MeshDataList.end()) {

		Data = new S_Mesh_Data();

		Data->NumVertex = Xfile.Mesh.lpMesh->GetNumVertices();

		CLONEVERTEX *pV;
		D3DXVECTOR3 BigPos , SmallPos;
		Xfile.Mesh.lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);

		Judg judg;
		for (DWORD No = 0; No < Data->NumVertex; No++) {
			if (No > 0) {
				judg.Pos_Big_Judg(&BigPos, &(pV + No)->Pos);
				judg.Pos_Small_Judg(&SmallPos, &(pV + No)->Pos);
			}
			else {
				BigPos = SmallPos = (pV + No)->Pos;
			}
		}



		Data->Pos_Big = BigPos;
		Data->Pos_Small = SmallPos;

		Xfile.Mesh.lpMesh->UnlockVertexBuffer();

		MeshDataList[FileName] = Data;
	}
	else {
		Data = MeshDataList[FileName];
	}

	Xfile.Data = *Data;

	return Xfile;
}

void XFileManagerData::AllDelete(void)
{
	for (auto itr = MeshDataList.begin(); itr != MeshDataList.end(); itr++) {
		delete itr->second;
	}
	MeshDataList.clear();
}
